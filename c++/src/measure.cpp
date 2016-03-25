/* measure.cpp */

#include <measure.hpp>

double getrusageSec()
{
	struct rusage t;
	struct timeval s;
	getrusage(RUSAGE_SELF, &t);
	s = t.ru_utime;
	return s.tv_sec + (double)s.tv_usec*1e-6;
}

long getrusageMem()
{
	struct rusage r;
	getrusage(RUSAGE_SELF, &r);
	return r.ru_maxrss;
}

/*

char command[MAX_STRING];
sprintf(command, "grep VmHWM /proc/%d/status", getpid());
system(command);

other method to measure memory, reference to
http://goyoki.hatenablog.com/entry/2013/05/11/031202

*/
