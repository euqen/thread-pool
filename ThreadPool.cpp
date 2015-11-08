#include "stdafx.h"
#include "ThreadPool.h"

CRITICAL_SECTION section;

ThreadPool::ThreadPool() {
	int defaultTreadsCount = 1;

	this->ThreadPool::ThreadPool(defaultTreadsCount);
}

ThreadPool::ThreadPool(int poolSize) {
	InitializeCriticalSection(&section);
	
	this->enabled = true;
	this->poolSize = poolSize;
	for (int i = 0; i < poolSize; i++) {
		this->threads.push_back(new Thread(&section));
	}
	this->handler = CreateThread(NULL, 0, controller, this, 0, NULL);

	Logger::info("Thread pull has beed initialized by " + std::to_string(poolSize) + " threads");
}

void ThreadPool::execute() {
	while (this->enabled) {
		Task * task = this->generateNewTask();
		Thread * thread = this->getAvailableThread();
		this->assignTask(task, thread);

		if (this->threads.size() > this->poolSize + 2) {
			this->destroy();
		}

		Sleep(5000);
	}
}

DWORD WINAPI ThreadPool::controller(LPVOID self) {
	Sleep(10); 
	ThreadPool * tp = (ThreadPool *)self;
	tp->execute();

	return 0;
}

Task* ThreadPool::generateNewTask() {
	Task *task = new Task();
	return task;
}


Thread * ThreadPool::getAvailableThread() {
	for (int i = 0; i < this->threads.size(); i++) {
		if (this->threads[i]->isAvailable) {
			return this->threads[i];
		}
	}

	Logger::warn("No threads available, needed to create a new one");
	
	Thread * thread = new Thread(&section);
	this->threads.push_back(thread);

	return thread;
}

void ThreadPool::assignTask(Task * task, Thread * thread) {
	EnterCriticalSection(&section);

	thread->queue.push(task);
	Logger::info("Assigned task to thread #" + std::to_string(thread->id));
	
	LeaveCriticalSection(&section);
}


void ThreadPool::destroy() {
	Logger::alert("Thread Pool destroying has been started");

	for (int i = 0; i < this->threads.size(); i++) {
		this->threads[i]->close();
		delete this->threads[i];
	}
	
	DeleteCriticalSection(&section);

	this->enabled = false;
	Logger::alert("Thread pool has been successfully destroyed.");

	ExitThread(0);
}