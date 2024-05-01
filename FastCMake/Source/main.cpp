#include <iostream>
#include "Generator.h"

using namespace youm;

int main(void)
{
	std::string path;
	std::cout << "Fast create a CMake project for C++" << std::endl;
	std::cout << "Please input your project path: ";
	std::cin >> path;
	std::cout << "Please input your project name: ";
	std::cin >> generator::options["project_name"];
	std::cout << "Please input your project cpp version: ";
	std::cin >> generator::options["cpp_version"];
	std::cout << "Please input your project cmake version: ";
	std::cin >> generator::options["cmake_version"];

	path += "/" + generator::options["project_name"];
	bool isCreated = generator::createDir(path);
	if (isCreated)
	{
		generator::createCMakeFile(path);
		generator::createDir(path + "/" + "Sources");
		generator::createDir(path + "/" + "Assets");
	}
	return 0;
}