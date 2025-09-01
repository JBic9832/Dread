#pragma once

#include <string>
#include <sstream>
#include <fstream>

namespace Dread {

class FileReader {
public:
	static std::string ReadTextFile(const std::string& file);

private:
	FileReader() {};
	~FileReader() {};
};

}
