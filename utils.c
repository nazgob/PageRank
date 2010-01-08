#include <utils.h>

extern int float_comparator(const void* a, const void* b)
{
    float* arg1 = (float*) a;
    float* arg2 = (float*) b;

    if(*arg1 < *arg2)
    {
	return -1;
    }
    else if(*arg1 == *arg2)
    {
	return 0;
    }
    else
    {
	return 1;
    }
}

extern int compare_floats(float a, float b)
{
    if (fabs(a - b) < 0.1) // just for unit testing, good enough
    {
	return 1;
    }
    return 0;
}

