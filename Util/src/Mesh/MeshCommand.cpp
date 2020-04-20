#include "MeshCommand.h"
#include "MeshInternal.h"

#include "../Core/StringUtility.h"

#include <iostream>
#include <chrono>
#include <cstring>

void UseageMesh(const char* name)
{
	std::cout << "Useage: " << name << " mesh [--format=<format>] <file> [<output_name>]" << std::endl;
	std::cout << "    --format=<format>: Specifies format of file. <format> can be one of the following:" << std::endl;
	std::cout << "                       - obj" << std::endl;
	std::cout << "                       If empty Jolt will determine the file format based off its extension" << std::endl;
	std::cout << "    <file>:            Name of file to convert" << std::endl;
	std::cout << "    <output_name>:     Name of the generated file, if empty the generated file will have the" << std::endl;
	std::cout << "                       same name of the input file with the extension \".jltmsh\"" << std::endl;
	std::cout << std::endl;
}

enum class FILE_FORMAT
{
	OBJ,
	UNKNOWN,
};

FILE_FORMAT StringToFormat(const char* str)
{
	if (strcmp(str, "obj") == 0)
		return FILE_FORMAT::OBJ;
	else
		return FILE_FORMAT::UNKNOWN;
}

std::string FormatToString(FILE_FORMAT format)
{
	switch (format)
	{
	case FILE_FORMAT::OBJ:
		return std::string("obj");
	
	case FILE_FORMAT::UNKNOWN:
	default:
		return std::string("unknown");
	}
}

void MeshCommand(int argc, char** argv)
{
    const char* prog_name = argv[0];
	if (argc == 2 || argc == 3 && strcmp(argv[2], "--help") == 0)
	{
		UseageMesh(prog_name);
		exit(EXIT_FAILURE);
	}
	// Determine file format
	FILE_FORMAT format;
	int file_name_argument_index = 2;
	if (IsChoiceCommandLineArg(argv[2], "format"))
	{
		file_name_argument_index++;
		format = StringToFormat(GetChoice(argv[2]).c_str());
	}
	else
	{
		// No format specifer, determine file format
		bool success;
		auto extension = GetExtension(argv[2], success);
		if (!success)
			format = FILE_FORMAT::UNKNOWN;
		else
			format = StringToFormat(extension.c_str());
	}

	// Determine file name
	if (argc <= file_name_argument_index)
	{
		std::cout << "No filename provided\n";
		UseageMesh(prog_name);
		exit(EXIT_FAILURE);
	}
	const char* filename = argv[file_name_argument_index];

	// Determine output name
	std::string output_name;
	if (argc == file_name_argument_index + 1)
	{
		output_name = StripExtension(filename) + ".jltmsh";
	}
	else if (argc == file_name_argument_index + 2)
	{
		output_name = std::string(argv[file_name_argument_index + 1]);
	}
	else
	{
	    std::cout << "Invalid number of arguments\n";
		UseageMesh(prog_name);
		exit(EXIT_FAILURE);
	}
			
			
	switch (format)
	{
	case FILE_FORMAT::OBJ:
	{
		auto beg = std::chrono::high_resolution_clock::now();
		std::vector<vec3> vPos;
		std::vector<vec3> vNorm;
		std::vector<vec2> vTex;
		std::vector<Index> iBuf;
		ModelFlags modelFlags;

		BufferObj(filename, vPos, vNorm, vTex, iBuf, modelFlags);

		std::vector<float> vertexBuffer;
		std::vector<unsigned int> indexBuffer;

		ExpandObj(vPos, vNorm, vTex, iBuf, vertexBuffer, indexBuffer, modelFlags);

		WriteToFile(output_name, vertexBuffer, indexBuffer, modelFlags);
		auto end = std::chrono::high_resolution_clock::now();

		auto duration = end - beg;
		std::cout << "Done! (" << (float)duration.count() / 1000000 << "ms)\n";
		break;
	}
			
	case FILE_FORMAT::UNKNOWN:
	default:
		std::cout << "Unknown file format" << std::endl;
		break;
	}		
	exit(EXIT_SUCCESS);
}