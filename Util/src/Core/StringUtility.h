#pragma once
#include <string>

std::string GetExtension(const char* file, bool& success);
std::string StripExtension(const char* file);
void TrimWhiteSpace(const char** string);

// Returns true if the string arg is of the from --expected=*, where * is a wild card (ie any substring)
bool IsChoiceCommandLineArg(const char* arg, const char* expected);

std::string GetChoice(const char* arg);