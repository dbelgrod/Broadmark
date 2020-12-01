

#pragma once

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#else  
#include <time.h>
#endif 

#include "Core/Results.h"


// High-resolution clock implementation
// This is one of the few windows-only parts of the code
class Clock {
private:
	#if defined(WIN32) || defined(_WIN32)
	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_reference;
	#else
	struct timespec m_freq;
	struct timespec m_reference;
	#endif

public:
	Clock() {
		#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceFrequency(&m_freq);
		#else
		clock_gettime(CLOCK_REALTIME, &m_freq);
		#endif
		reset();
	}

	void reset() {
		#if defined(WIN32) || defined(_WIN32)
		QueryPerformanceCounter(&m_reference);
		#else
		clock_gettime(CLOCK_REALTIME, &m_reference);
		#endif
	}
	double getAndReset() {
		#if defined(WIN32) || defined(_WIN32)
		const LARGE_INTEGER reference = m_reference;
		QueryPerformanceCounter(&m_reference);
		// No need to bloat log files with smaller than 10^{-6} values
		const double timeInSeconds = (double)((m_reference.QuadPart - reference.QuadPart) / (double)m_freq.QuadPart);
		#else
		const struct timespec reference = m_reference;
		clock_gettime(CLOCK_REALTIME, &m_reference);
		const double timeInSeconds = (double)((m_reference.tv_sec - reference.tv_sec) / (double)m_freq.tv_sec);
		return timeInSeconds > 0.000001f ? timeInSeconds : 0;
	}
};

template<typename Action>
inline double Measure(const Action action) {
	Clock clock;
	action();

	return clock.getAndReset();
}

template<typename Action>
inline void MeasureAndReport(const char* actionName, const Action action) {
	Results::Report(actionName, Measure(action));
}
