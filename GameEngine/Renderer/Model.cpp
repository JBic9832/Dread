#include "Model.h"
#include "Core/FileReader.h"

namespace Dread {

Model::Model(const std::string& file) 
	: m_FileName { file } {
	std::string fileContents = FileReader::ReadTextFile(m_FileName);

	m_JSON = nlohmann::json::parse(fileContents);

	m_ModelData = getData();
}

std::vector<unsigned char> Model::getData() {
	std::string bytesText;
	std::string uri = m_JSON["buffers"][0];

}

}
