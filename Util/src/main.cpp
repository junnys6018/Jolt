#include <iostream>

#include "mesh.h"

void Useage(const char* name)
{
	std::cout << "Useage: " << name << " <command> [<args>]\n" << std::endl;
	std::cout << "Commands:\n";
	std::cout << "    mesh <filepath> [output name]\n";
}


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		Useage(argv[0]);
		return 0;
	}

	if (strcmp(argv[1], "mesh "))
	{
		std::vector<vec3> vPos;
		std::vector<vec3> vNorm;
		std::vector<vec2> vTex;
		std::vector<Index> iBuf;
		ModelFlags modelFlags;

		BufferObj(argv[2], vPos, vNorm, vTex, iBuf, modelFlags);

		std::vector<float> vertexBuffer;
		std::vector<unsigned int> indexBuffer;

		ExpandObj(vPos, vNorm, vTex, iBuf, vertexBuffer, indexBuffer, modelFlags);

		WriteToFile("data", vertexBuffer, indexBuffer, modelFlags);
	}
	else
	{
		Useage(argv[0]);
	}

	return 0;
}
