#include "GltfLoader.h"
#include "Core/Logger.h"

namespace Dread {

Model GLTFLoader::CreateMeshFromGLTF(const std::string &gltfFile) {
	Model model(gltfFile);

	tinygltf::Model gltfModel = loadModel(gltfFile);
	
	return model;
}

tinygltf::Model GLTFLoader::loadModel(const std::string& fileName) {
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err, warn;

	bool result = loader.LoadASCIIFromFile(&model, &err, &warn, fileName);
	
	if (!warn.empty()) {
		DREAD_CORE_WARN(warn);
	}

	if (!err.empty()) {
		DREAD_CORE_ERROR(err);
	}

	if (!result) {
		DREAD_CORE_ERROR("FAILED TO LOAD GLTF MODEL: {0}", fileName);
	} else {
		DREAD_CORE_INFO("Loaded glTF model: {0}", fileName);
	}

	return model;
}

}
