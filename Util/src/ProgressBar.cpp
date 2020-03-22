#include <iostream>
#include <chrono> // For ms
#include <thread> // For this_thread
#include "ProgressBar.h"

using namespace std::chrono_literals;
#define PBSTR "|||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH sizeof(PBSTR)

void printProgress(double percentage, const char* message)
{
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r[%.*s%*s]%3d%% %-20s", lpad, PBSTR, rpad, "", val, message);
	fflush(stdout);
}

void bar(double* percentage, const char* message)
{
	while (*percentage < 1.0f)
	{
		printProgress(*percentage, message);
		std::this_thread::sleep_for(100ms);
	}
	printProgress(*percentage, message);
	std::cout << std::endl;
}