#pragma once

#include "Renderer/Mesh.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/tiny_gltf/tiny_gltf.h"
#include <string>

namespace Dread {

class GLTFLoader {
public:
	GLTFLoader();
	~GLTFLoader();

	static Mesh CreateMeshFromGLTF(const std::string& gltfFile);

private:
	static tinygltf::Model LoadModel(const std::string& fileName);

};

}
