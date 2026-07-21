#pragma once
#include <string>
#include <regex>

class ValidService {
public:
	static bool isValidTimeFormat(cosnt std::string& timeStr) {
		std::regex timePattern("^(0[1-9]|1[0-2]):[0-5][0-9](am|pm)$");
		return std::regex_match(timeStr, timePattern);
	}

	static bool isValidId(const std::string* id) {
		return !id.empty();
	}
}
