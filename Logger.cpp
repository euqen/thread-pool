#include "stdafx.h"
#include "logger.h"
#include <Windows.h>
#include <iostream>


void Logger::info(std::string message) {
	std::cout <<" INFO: " << message << std::endl;
}

void Logger::warn(std::string message) {
	std::cout << "WARN: " << message << std::endl;
}

void Logger::debug(std::string message) {
	std::cout << "DEBUG: " << message << std::endl;
}

void Logger::alert(std::string message) {
	std::cout << "ALERT: " << message << std::endl;
}