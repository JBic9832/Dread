#pragma once

#include "Core/Application.h"
#include "Core/Logger.h"
#include "RenderPass.h"
#include "Renderer/Renderer.h"
#include "Renderer/ResourceManager.h"
#include "Renderer/Shader.h"
#include "SceneManagement/GameObject.h"

#include <gl/gl.h>
#include <glad/glad.h>
#include <string>
#include <vector>

namespace Dread {

class GeometryPass : public RenderPass {
public:
    GeometryPass() { 
        Setup(); 
        ResourceManager::LoadShader(RESOURCES_PATH "geopass_vert.glsl",  RESOURCES_PATH "geopass_frag.glsl", "geopass");
        ResourceManager::LoadShader(RESOURCES_PATH "deferred_vert.glsl",RESOURCES_PATH  "deferred_frag.glsl", "deffered_lighting");
    }

    void Render() override {
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model {1.0f};

        // Geometry Pass
        Shader gPassShader = ResourceManager::GetShader("geopass");
        Shader basicShader = ResourceManager::GetShader("basic");
        gPassShader.Bind();
        gPassShader.SetUniformMatrix4f("uProjection", Application::GetProjectionMatrix());
        gPassShader.SetUniformMatrix4f("uView", Renderer::GetMainCamera()->GetViewMatrix());
        for (GameObject& go : Renderer::GameObjectContainer) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, go.m_Transform.m_Position);
            gPassShader.SetUniformMatrix4f("uModel", model);

            go.DrawMesh();
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Shader lPassShader = ResourceManager::GetShader("deferred_lighting");
        lPassShader.Bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);

        for (unsigned int i = 0; i < lightPositions.size(); i++)
        {
            lPassShader.SetUniformVec3f("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
            lPassShader.SetUniformVec3f("lights[" + std::to_string(i) + "].Color", lightColors[i]);
            // update attenuation parameters and calculate radius
            const float linear = 0.7f;
            const float quadratic = 1.8f;
            lPassShader.SetUniformFloat("lights[" + std::to_string(i) + "].Linear", linear);
            lPassShader.SetUniformFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
        }

        lPassShader.SetUniformVec3f("viewPos", Renderer::GetMainCamera()->GetCameraPosition());

        Renderer::DrawScreenQuad();

        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glm::vec2 winSize = Application::GetWindowSize();
        glBlitFramebuffer(0, 0, winSize.x, winSize.y, 0, 0, winSize.x, winSize.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Setup() override {
        glGenFramebuffers(1, &gBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

        constructTextureBuffer(gPosition, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0);
        constructTextureBuffer(gNormal, GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT1);
        constructTextureBuffer(gAlbedo, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT2);

        unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, attachments);

        int windowWidth = Application::GetWindowSize().x;
        int windowHeight = Application::GetWindowSize().y;

        // Add a depth buffer to the geometry framebuffer
        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);


        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            DREAD_CORE_ERROR("Framebuffer not complete in GeometryPass: {0}", status);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Create lights at random positions with random colors
        for (unsigned int i = 0; i < NR_LIGHTS; i++) {
            // calculate slightly random offsets
            float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
            float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
            float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
            lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
            // also calculate random color
            float rColor = static_cast<float>(((rand() % 100) / 200.0f) +
                                              0.5); // between 0.5 and 1.0
            float gColor = static_cast<float>(((rand() % 100) / 200.0f) +
                                              0.5); // between 0.5 and 1.0
            float bColor = static_cast<float>(((rand() % 100) / 200.0f) +
                                              0.5); // between 0.5 and 1.0
            lightColors.push_back(glm::vec3(rColor, gColor, bColor));
        }

        Shader lPassShader = ResourceManager::GetShader("deferred_lighting");

        // Setup lighting pass shader
        lPassShader.Bind();
        lPassShader.SetUniformInt("gPosition", 0);
        lPassShader.SetUniformInt("gNormal", 1);
        lPassShader.SetUniformInt("gAlbedoSpec",2);
    }

private:
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gAlbedo;

    const int NR_LIGHTS = 5;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;

    void constructTextureBuffer(unsigned int& handle, int internalFormat, int format, int type, int attachment) {
        int windowWidth = Application::GetWindowSize().x; 
        int windowHeight = Application::GetWindowSize().y;

        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, windowWidth, windowHeight, 0, format, type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, handle, 0);
    }
};

}