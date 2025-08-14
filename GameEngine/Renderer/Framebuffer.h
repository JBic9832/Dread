#pragma once

#include <glad/glad.h>

namespace Dread {

class Framebuffer {
public:
	Framebuffer(const int width, const int height);
	~Framebuffer();

	void BindFramebuffer(const unsigned int target) const;
	void SetColorFormat(const int internalColorFormat);
	void SetAttachment(const unsigned int attachment);
	void SetWidth(const int width);
	void SetHeight(const int height);
	void AttachRenderBuffer(const unsigned int internalFormat);

private:
	// TODO:
	// Needs to rebuild frame buffer in cases of 
	// viewport resize, change in requirements, etc.
	void rebuildFramebuffer();

private:
	unsigned int m_RendererId;

	// Not required
	unsigned int m_RenderBuffer = 0;

	// Default values for drawing to texture
	unsigned int m_FramebufferTarget = GL_FRAMEBUFFER;
	int          m_InternalColorFormat = GL_RGB;
	unsigned int m_Attachment = GL_COLOR_ATTACHMENT0;

	int          m_Width, m_Height;
};

}
