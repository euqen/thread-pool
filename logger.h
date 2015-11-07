#pragma once
#include <string>

using namespace std;

class Logger {
	public:
		static void info(std::string message);
		static void warn(std::string message);
		static void debug(std::string message);
		static void alert(std:: string message);
};