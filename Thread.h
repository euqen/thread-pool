#include "Task.h"
#include <queue>

using namespace std;

class Thread {
	public:
		Thread(CRITICAL_SECTION * section);
		HANDLE handler;
		queue<Task *> queue;
		bool isAvailable;
		bool exited;
		DWORD id;
		void close();
	private:
		CRITICAL_SECTION * section;
		void execute();
		static DWORD WINAPI controller(LPVOID self);
};