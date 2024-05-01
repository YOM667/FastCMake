#include "Generator.h"

namespace youm::generator
{
	std::map<std::string, std::string> options;
	bool createDir(const std::string & path)
	{
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
			return true;
		}
		return false;
	}
	void createCMakeFile(const std::string& path)
	{
		// read cmake build file
		std::ifstream cmakeFile;
		std::stringstream cmakeContentStream;
		std::string cmakeCode;
		cmakeFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            cmakeFile.open("./CMakeLists.txt");
            // read file's buffer contents into streams
			cmakeContentStream << cmakeFile.rdbuf();
			cmakeCode = cmakeContentStream.str();
			// close file handlers
			cmakeFile.close();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "Error: FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
		//create CMakeLists.txt file in user's project
		std::ofstream outStream;
		try
		{
			outStream.exceptions(std::ofstream::failbit | std::ofstream::badbit);
			outStream.open(path + "/CMakeLists.txt", std::ios::app);
			outStream.exceptions(std::ofstream::goodbit);
		}
		catch (std::ofstream::failure const& exception)
		{
			std::cout << exception.what() << std::endl;
		}
		outStream << regexReplace(cmakeCode);
		outStream.close();
	}
	std::string regexReplace(const std::string& text)
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
}