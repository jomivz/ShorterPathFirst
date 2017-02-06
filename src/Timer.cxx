#include "../inc/Timer.h"

#ifndef __TIMER_CPP__
#define __TIMER_CPP__

int Timer::start()
{ 
	return gettimeofday(&tv1,&tz);
}
int Timer::stop()
{
	return gettimeofday(&tv2,&tz);
}
long Timer::getTime()
{
	diff=(tv2.tv_sec-tv1.tv_sec) * 1000000L + \
          (tv2.tv_usec-tv1.tv_usec);
	return diff/1000;
}

#endif
