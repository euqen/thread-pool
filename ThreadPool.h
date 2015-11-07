#include <vector>
#include <Windows.h>
#include "Thread.h"
#include "logger.h"

using namespace std;

class ThreadPool {
	public:
		ThreadPool();
		ThreadPool(int threadsCount);
		void execute();
		static DWORD WINAPI controller(LPVOID self);
		void destroy();
		bool enabled;
		bool poolSize;
	private:
		std::vector<Thread*> threads;
		Thread * getAvailableThread();
		Task *generateNewTask();
		void assignTask(Task * task, Thread * thread);
		HANDLE handler;
};