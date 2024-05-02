#include "Generator.h"

namespace youm::generator
{
	bool Generator::createDir(const std::string & dir, DirHanler hanler, bool inRoot)
	{
		std::string directory;
		if (inRoot) {
			directory = (path + "/" + name + "/" + dir);
		}
		else
		{
			directory = (path + "/" + dir);
		}
		if (!std::filesystem::exists(directory))
		{
			std::filesystem::create_directory(directory);
			if (hanler != nullptr)
			{
				hanler(DirOperator(directory));
			}
			return true;
		}
		return false;
	}
	bool Generator::createDirInPath(const std::string& dir)
	{
		return createDir(dir, nullptr, false);
	}
	bool Generator::createDirInRoot(const std::string& dir)
	{
		return createDir(dir, nullptr);
	}

	void Generator::createCMakeFile()
	{
		std::string code = readFromFile("./Assets/CMakeLists.txt");
		writeToFile(path + "/" + name + "/" + "CMakeLists.txt", regexReplace(code));
	}
	std::string Generator::readFromFile(const std::string& filename)
	{
		// read file
		std::ifstream file;
		std::stringstream contentStream;
		std::string content;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			file.open(filename);
			// read file's buffer contents into streams
			contentStream << file.rdbuf();
			content = contentStream.str();
			// close file handlers
			file.close();
			return content;
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "Error: FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
			return "error!!";
		}
	}
	void Generator::writeToFile(const std::string& filename,const std::string& text)
	{
		//create CMakeLists.txt file in user's project
		std::ofstream outStream;
		try
		{
			outStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
			outStream.open(filename, std::ios::app);
			outStream.exceptions(std::ofstream::goodbit);
		}
		catch (std::ofstream::failure const& exception)
		{
			std::cout << exception.what() << std::endl;
		}
		outStream << text;
		outStream.close();
	}
	std::string Generator::regexReplace(const std::string& text)
	{
		try
		{
			std::string result = text;
			std::regex pattern(R"(\&\{\w+\})");
			std::smatch matches;
			std::sregex_iterator it(text.begin(), text.end(), pattern);
			std::sregex_iterator end;
			int backIndex = 0;

			std::map<std::string, std::string>::iterator backIter;
			for (; it != end; ++it)
			{
				matches = *it;
				std::map<std::string, std::string>::iterator iter;

				for (iter = options.begin(); iter != options.end(); iter++)
				{
					std::string matchString = "&{" + iter->first + "}";
					if (matchString == matches.str())
					{
						result = result.replace(matches.position() - backIndex, matchString.size(), iter->second);
						backIndex += matchString.size() - options[iter->first].size();
					}

				}
			}
			return result;
		}
		catch (const std::regex_error& e)
		{
			std::cout << "regex_error: what(): " << e.what() << std::endl;
			return "replaced_text_error";
		}

	}
	Options Generator::getOptions()
	{
		return this->options;
	}


	void DirOperator::createFile(const std::string& file, const std::string& text)
	{
		std::ofstream outStream;
		try
		{
			outStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
			outStream.open(dir + "/" + file, std::ios::app);
			outStream.exceptions(std::ofstream::goodbit);
		}
		catch (std::ofstream::failure const& exception)
		{
			std::cout << exception.what() << std::endl;
		}
		outStream << text;
		outStream.close();
	}
}