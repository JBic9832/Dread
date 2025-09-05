#pragma once

#include "Renderer/Model.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <vendor/tiny_gltf/tiny_gltf.h>
#include <string>
#include <vendor/json/json.hpp>

namespace Dread {

class GLTFLoader {
public:
	static Model CreateMeshFromGLTF(const std::string& gltfFile);

private:
	GLTFLoader();
	~GLTFLoader();
	static tinygltf::Model loadModel(const std::string& fileName);
	static nlohmann::json parseJSONFromFile(const std::string& fileName);


};

}
