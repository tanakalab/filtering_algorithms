/* measure.cpp */

#include <measure.hpp>

double gettimeofday_sec()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}

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
