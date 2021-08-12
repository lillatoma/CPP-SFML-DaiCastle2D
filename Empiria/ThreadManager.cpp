#include "ThreadManager.h"

int ThreadManager::get_running_threads()
{
	return Threads.size() + 1;
}

bool ThreadManager::is_free_thread_available()
{
	return Threads.size() + 1 <= MaxThreadSize;
}

void ThreadManager::set_max_threads(int threadn)
{
	if (threadn > MaxThreadSize)Threads.reserve(threadn + 1);
	MaxThreadSize = threadn;
}

int ThreadManager::get_max_threads() const
{
	return MaxThreadSize;
}





ThreadManager g_Threads;