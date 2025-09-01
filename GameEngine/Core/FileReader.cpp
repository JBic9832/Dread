#include "FileReader.h"
#include "Core/Logger.h"

namespace Dread {

std::string FileReader::ReadTextFile(const std::string &filePath) {
	std::string fileContents;

	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(filePath);
		std::stringstream fileStream;

		fileStream << file.rdbuf();

		file.close();

		fileContents = fileStream.str();
	} catch (std::ifstream::failure e) {
		DREAD_CORE_ERROR("FAILED TO READ FILE {0}: {1}", filePath, e.code().value());
	}

	return fileContents;

}

}
