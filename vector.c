#include <vector.h>

extern void vector_normalize(float* v, size_t dimension)
{
    float factor = v[0];
    v[0] = 1.0;
    for(size_t i = 1; i < dimension; ++i)
    {
	v[i] = v[i] / factor;
    }
}

extern void vector_sort(float* v, size_t dimension)
{
    qsort (v, dimension, sizeof(float), float_comparator);
}

