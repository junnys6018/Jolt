#include "StringUtility.h"

#include <string>
#include <iostream>
#include <cstring>

void TrimWhiteSpace(const char** string)
{
	while(std::isspace(**string))
		(*string)++;
}

std::string GetExtension(const char* file, bool& success)
{
	const char* last_dot = strrchr(file, '.');
    if (last_dot == NULL)
	{
        success = false;
		return std::string();
	}
    success = true;
	return std::string(last_dot + 1);
}

// If file has no extension, return file
std::string StripExtension(const char* file)
{
	const char* last_dot = strrchr(file, '.');
	if (last_dot == NULL)
	{
		return std::string(file);
	}
	else
	{
		return std::string(file, last_dot - file);
	}
}

// Returns true if the string arg is of the from --expected=*, where * is a wild card (ie any substring)
bool IsChoiceCommandLineArg(const char* arg, const char* expected)
{
	if (arg[0] != '-' || arg[1] != '-')
		return false;
	
	const char* first_equal_sign = strchr(arg, '=');
	if (first_equal_sign == NULL) // No '=' found
		return false;

    // name of the choice is a different length as the expected name
	if (first_equal_sign - arg - 2 != strlen(expected))
		return false;

    // ... and a different string
	if (strncmp(arg + 2, expected, strlen(expected)) != 0)
		return false;

	return true;
}

std::string GetChoice(const char* arg)
{
	const char* first_equal_sign = strchr(arg, '=');
	return std::string(first_equal_sign + 1);
}

void Test(const char* arg, const char* expected, bool result)
{
	if (IsChoiceCommandLineArg(arg, expected) == result)
		std::cout << "Test Passed\n";
	else
		std::cout << "Test Failed\n";
}

void TestAll()
{
	Test("-fmt=true", "fmt", false);
	Test("mesh", "blah", false);
	Test("--foobar","bar", false);
	Test("--foo=bar", "f", false);
	Test("--foo=bar", "fooo", false);
	Test("--foo=bar", "goo", false);

	Test("--configuration=bad", "configuration", true);
	Test("--fmt=true", "fmt", true);
}