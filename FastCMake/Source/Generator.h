#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>


namespace youm::generator
{
	extern std::map<std::string, std::string> options;

	bool createDir(const std::string & path);

	void createCMakeFile(const std::string& path);

	std::string regexReplace(const std::string& text);
}