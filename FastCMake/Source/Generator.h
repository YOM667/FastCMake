#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <functional>

namespace youm::generator
{

	class DirOperator
	{
	public:
		const std::string& dir;
		DirOperator(const std::string& dir) : dir(dir){}
		void createFile(const std::string& file, const std::string& text);
	};
	typedef std::map<std::string, std::string> Options;

	typedef std::function<void(DirOperator)> DirHanler;

	class Generator
	{
	private:
		const std::string& path;
		const std::string& name;
		Options options;
	public:
		Generator(
			const std::string& path, 
			const std::string& name,
			Options options
		) : path(path) ,name(name), options(options) {
			createDirInPath(name);
			createCMakeFile();
		}

		bool createDir(const std::string& dir, DirHanler createFiles, bool inRoot = true);

		bool createDirInPath(const std::string& dir);

		bool createDirInRoot(const std::string& dir);

		void createCMakeFile();

		std::string readFromFile(const std::string& filename);

		void writeToFile(const std::string& filename, const std::string& text);

		std::string regexReplace(const std::string& text);

		Options getOptions();

	};


}