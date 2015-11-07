#include "stdafx.h"
#include "logger.h"
#include "Thread.h"

Thread::Thread(CRITICAL_SECTION * section) {
	this->section = section;
	this->exited = false;
	this->isAvailable = true;
	this->handler = CreateThread(NULL, 0, controller, this, 0, &this->id);
	Logger::info("New thread has beed created #" + std::to_string(this->id));
}

void Thread::execute() {
	while (!this->exited) {

		if (this->queue.size()) {
			Task *task = this->queue.front();
			this->isAvailable = false;
			task->execute();
			this->queue.pop();
			this->isAvailable = true;
		}
		else {
			Sleep(3000); //check queue after 3 sec
		}

	}
}

DWORD WINAPI Thread::controller(LPVOID self) {
	Thread *thread = (Thread*)self;
	thread->execute();

	return 0;
}

void Thread::close() {
	this->exited = true;
	WaitForSingleObject(this->handler, INFINITE);
	Logger::alert("Thread #" + std::to_string(this->id) + " has been closed");
}