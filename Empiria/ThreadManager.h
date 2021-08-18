#pragma once
#include "includes.h"
#include <thread>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

struct alpha_thread
{
	std::thread* Thread;
	int t_id;
	dc_clock BeginClock;


	alpha_thread()
	{
		BeginClock.Update();
	}

	template <typename Func> alpha_thread(Func f,int i)
	{
		t_id = i;
		Thread = new std::thread(f);

	
	}

	~alpha_thread()
	{
		float diff = 0.001f*BeginClock.deltaTime();


		Thread->detach();
	}
};

class ThreadManager
{
public:
	int get_running_threads();
	void set_max_threads(int thr);
	int get_max_threads() const;
	bool is_free_thread_available();

	template <typename Func, typename... Args> void Run(Func *func, Args... args);
private:
	int MaxThreadSize = 1;
	std::vector<alpha_thread*> Threads;
};

template <typename Func, typename... Args> void ThreadManager::Run(Func *func, Args... args)
{
	using namespace std::literals::chrono_literals;
	static int identity = 0;


	if (!is_free_thread_available())
	{
		(*func)(args...);
		return;
	}

	auto F = [this, func, args...]() {
		dc_clock C; C.Update();
		(*func)(args...);
		bool Sta = true;
		while (Sta)
		{
			for (int i = 0; i < Threads.size(); i++)
			{
				//char* NewBuffer = new char[64];
				//sprintf(NewBuffer, "\nthreadcheck: %d - %d", identity, Threads[i]->t_id);
				//g_Mes.push_back(NewBuffer);
				if (identity == Threads[i]->t_id)
				{
					//Threads[i]->~alpha_thread();
					Threads.erase(Threads.begin() + i);
					Sta = false;
					break;
				}
			}
			if (Sta)std::this_thread::sleep_for(1ms);
		}

	};
	alpha_thread* T = new alpha_thread(F,identity);
	Threads.push_back(T);
	identity++;
}


extern ThreadManager g_Threads;
