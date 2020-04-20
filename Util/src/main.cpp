#include <iostream>
#include <cstring>
#include "Mesh/MeshCommand.h"

void Useage(const char* name)
{
	std::cout << "Useage: " << name << " <command> [--help | <args>]\n" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "    --help: Print help for the chosen command" << std::endl;
	std::cout << "Commands:" << std::endl;;
	std::cout << "    mesh: Convert a 3D model into Jolt mesh file" << std::endl;
	std::cout << std::endl;
}



int main(int argc, char** argv)
{
	const char* prog_name = argv[0];
	if (argc >= 2)
	{
		if (strcmp(argv[1], "mesh") == 0)
		{
			MeshCommand(argc, argv);
		}
	}

	Useage(prog_name);
	return 0;
}
