#include "stdafx.h"
#include "Task.h"
#include <iostream>
#include "logger.h";

Task::Task() {
	int maxTaskTimeMilliseconds = 50000;
	srand(time(0));

	this->task = /*rand() %*/ maxTaskTimeMilliseconds;
}

void Task::execute() {
	/*
		Here we will simulate execution of some task
	*/

	Logger::info("Thread No. " + std::to_string(GetCurrentThreadId()) + " began task execution");
	
	Sleep(this->task);
	
	Logger::info("Thread No. " + std::to_string(GetCurrentThreadId()) + " finished task execution");

}