#include <windows.h>
#include <ctime>

using namespace std;

class Task {
	public:
		Task();
		void execute();
	
	private:
		int task;
};