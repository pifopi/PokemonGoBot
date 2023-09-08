#pragma once

#include "types.h"

#include <string>
#include <vector>

namespace Utils
{
	std::string GetStringFromType(Type type);
	std::vector<std::string> Split(const std::string& string, char delim);
	std::string GetCSVStringFromBool(bool value);
	std::string GetHyperLinkFromMove(const Move& move);
	bool RemoveSubstringFront(std::string& mainString, const std::string& subString);
	bool RemoveSubstringBack(std::string& mainString, const std::string& subString);
	bool RemoveSubstringMidle(std::string& mainString, const std::string& subString);
}
