#include "stdafx.h"
#include "ThreadPool.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ThreadPool *pool = new ThreadPool(2);

	while (pool->enabled) {
		Sleep(1000);
	}
	
	system("pause");

	return 0;
}

