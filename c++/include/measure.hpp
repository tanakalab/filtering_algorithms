/* measure.hpp */

#ifndef __RBTRIE_MEASURE_HPP__
#define __RBTRIE_MEASURE_HPP__

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double getrusageSec();
long getrusageMem();

#endif
