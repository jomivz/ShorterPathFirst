#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#ifndef __TIMER_H__
#define __TIMER_H__

class Timer 
{
 private :
	struct timeval tv1,tv2;
	struct timezone tz;
	long long diff;
 public :
 //	Timer(){};
	int start();
	int stop();
	long getTime();
};

#endif
