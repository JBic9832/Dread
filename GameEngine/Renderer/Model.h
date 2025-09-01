#pragma once

#include "Mesh.h"
#include <vendor/json/json.hpp>
#include <string>

namespace Dread {

class Model {
public:
	Model(const std::string& file);

private:
	const std::string& m_FileName;
	std::vector<unsigned char> m_ModelData;
	nlohmann::json m_JSON;
};

}
