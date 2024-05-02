#include <iostream>
#include "Generator.h"

using namespace youm;

int main(void)
{
	generator::Options options;
	//Init Generator
	std::string path;
	std::cout << "Fast create a CMake project for C++" << std::endl;
	std::cout << "Please input your project path: ";
	std::cin >> path;

	//Users' configuration
	std::cout << "Please input your project name: ";
	std::cin >> options["project_name"];
	std::cout << "Please input your project cpp version: ";
	std::cin >> options["cpp_version"];
	std::cout << "Please input your project cmake version: ";
	std::cin >> options["cmake_version"];

	generator::Generator generator(path, options["project_name"], options);

	auto callback = [&generator](generator::DirOperator dirOperator) -> void {
		dirOperator.createFile("main.cpp", generator.readFromFile("./Assets/main.cpp"));
		dirOperator.createFile("log.cpp", generator.readFromFile("./Assets/log.cpp"));
		dirOperator.createFile("log.h", generator.readFromFile("./Assets/log.h"));
		dirOperator.createFile("utility.cpp", generator.readFromFile("./Assets/utility.cpp"));
		dirOperator.createFile("utility.h", generator.readFromFile("./Assets/utility.h"));
	};
	generator.createDir("Sources", callback);

	generator.createDirInRoot("Assets",);
	
	return 0;
}