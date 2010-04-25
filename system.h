
#ifndef __SYSTEM_HEADER__
#define __SYSTEM_HEADER__

#include <set>
#include <SDL/SDL.h>

#include "utils.h"
#include "defs.h"

#include "mode_manager.h"

#define NO_THREADS 0
#define SDL_THREADS 1

/* Set this to NO_THREADS to disable threads. Set this to SDL_THREADS to use
 * SDL Threads. */
#define THREAD_TYPE SDL_THREADS

#if (THREAD_TYPE == SDL_THREADS)
	#include <SDL/SDL_thread.h>
	#include <SDL/SDL_mutex.h>
	typedef SDL_Thread Thread;
	typedef SDL_sem Semaphore;
#else
	typedef int Thread;
	typedef int Semaphore;
#endif

const uint32 SYSTEM_INFINITE_TIME = 0xFFFFFFFF;

const int32 SYSTEM_LOOP_INFINITE = -1;

enum SYSTEM_TIMER_STATE {
	SYSTEM_TIMER_INVALID  = -1,
	SYSTEM_TIMER_INITIAL  =  0,
	SYSTEM_TIMER_RUNNING  =  1,
	SYSTEM_TIMER_PAUSED   =  2,
	SYSTEM_TIMER_FINISHED =  3,
	SYSTEM_TIMER_TOTAL    =  4
};

extern SystemEngine* SystemManager;

extern bool SYSTEM_DEBUG;

class SystemTimer {
	friend class SystemEngine;

public:
	SystemTimer();

	SystemTimer(uint32 duration, int32 number_loops = 0, hoa_mode_manager::GameMode* mode_owner = NULL) : _state(SYSTEM_TIMER_INVALID)
		{ Initialize(duration, number_loops, mode_owner); }

	~SystemTimer();

	void Initialize(uint32 duration, int32 number_loops = 0, hoa_mode_manager::GameMode* mode_owner = NULL);

	void Reset()
		{ if (_state != SYSTEM_TIMER_INVALID) { _state = SYSTEM_TIMER_INITIAL; _time_expired = 0; _times_completed = 0; } }

	void Run()
		{ if (IsInitial() || IsPaused()) _state = SYSTEM_TIMER_RUNNING; }

	void Pause()
		{ if (IsRunning()) _state = SYSTEM_TIMER_PAUSED; }

	void Finish()
		{ _state = SYSTEM_TIMER_FINISHED; }

	bool IsInitial() const
		{ return (_state == SYSTEM_TIMER_INITIAL); }

	bool IsRunning() const
		{ return (_state == SYSTEM_TIMER_RUNNING); }

	bool IsPaused() const
		{ return (_state == SYSTEM_TIMER_PAUSED); }

	bool IsFinished() const
		{ return (_state == SYSTEM_TIMER_FINISHED); }

	float PercentComplete();

	void SetDuration(uint32 duration);

	void SetNumberLoops(int32 number_loops);

	void SetModeOwner(hoa_mode_manager::GameMode* mode_owner);

	SYSTEM_TIMER_STATE GetState() const
		{ return _state; }

	uint32 GetDuration() const
		{ return _duration; }

	int32 GetNumberLoops() const
		{ return _number_loops; }

	hoa_mode_manager::GameMode* GetModeOwner() const
		{ return _mode_owner; }

	uint32 GetTimeExpired() const
		{ return _time_expired; }

	uint32 GetTimeLeft() const
		{ return (_duration - _time_expired); }

	uint32 GetTimesCompleted() const
		{ return _times_completed; }

	uint32 GetCurrentLoop() const
		{ return _times_completed; }

private:
	SYSTEM_TIMER_STATE _state;

	uint32 _duration;

	int32 _number_loops;

	hoa_mode_manager::GameMode* _mode_owner;

	uint32 _time_expired;

	uint32 _times_completed;

	void _UpdateTimer();
};

class SystemEngine : public hoa_utils::Singleton<SystemEngine> {
	friend class hoa_utils::Singleton<SystemEngine>;
	friend class SystemTimer;

public:
	~SystemEngine();

	bool SingletonInitialize();

	void InitializeTimers();

	void InitializeUpdateTimer()
		{ _last_update = SDL_GetTicks(); _update_time = 1; }

	void UpdateTimers();

	void ExamineSystemTimers();

	uint32 GetUpdateTime() const
		{ return _update_time; }

	void SetPlayTime(const uint8 h, const uint8 m, const uint8 s)
		{ _hours_played = h; _minutes_played = m; _seconds_played = s; _milliseconds_played = 0; }

	uint8 GetPlayHours() const
		{ return _hours_played; }

	uint8 GetPlayMinutes() const
		{ return _minutes_played; }

	uint8 GetPlaySeconds() const
		{ return _seconds_played; }

	std::string GetLanguage() const
		{ return _language; }

	void SetLanguage(std::string lang);

	bool NotDone() const
		{ return _not_done; }

	void ExitGame()
		{ _not_done = false; }

	template <class T> Thread * SpawnThread(void (T::*)(), T *);
	void WaitForThread(Thread * thread);

	void LockThread(Semaphore *);
	void UnlockThread(Semaphore *);
	Semaphore * CreateSemaphore(int max);
	void DestroySemaphore(Semaphore *);

private:
	SystemEngine();

	uint32 _last_update;

	uint32 _update_time;

	uint8 _hours_played;
	uint8 _minutes_played;
	uint8 _seconds_played;

	uint16 _milliseconds_played;

	bool _not_done;

	std::string _language;

	std::set<SystemTimer*> _system_timers;
};


template <class T> struct generic_class_func_info
{
	static int SpawnThread_Intermediate(void * vptr) {
		((((generic_class_func_info <T> *) vptr)->myclass)->*(((generic_class_func_info <T> *) vptr)->func))();
		return 0;
	}

	T * myclass;
	void (T::*func)();
};


template <class T> Thread * SystemEngine::SpawnThread(void (T::*func)(), T * myclass) {
#if (THREAD_TYPE == SDL_THREADS)
	Thread * thread;
	static generic_class_func_info <T> gen;
	gen.func = func;
	gen.myclass = myclass;

	thread = SDL_CreateThread(gen.SpawnThread_Intermediate, &gen);
	if (thread == NULL) {
		PRINT_ERROR << "Unable to create thread: " << SDL_GetError() << std::endl;
		return NULL;
	}
	return thread;
#elif (THREAD_TYPE == NO_THREADS)
	(myclass->*func)();
	return 1;
#else
	PRINT_ERROR << "Invalid THREAD_TYPE." << std::endl;
	return 0;
#endif
}

#endif
