#include <vector.h>

extern void vector_init(vector* v, size_t size)
{
    v->size = size;
    v->elements = (float*)malloc(sizeof(float) * v->size);
}

extern void vector_free(vector* v)
{
    assert(v != NULL);
    free(v->elements);
    v->elements = NULL;
    v->size = 0;
    v = NULL;
}

extern void vector_normalize(vector* v)
{
    assert(v != NULL);
    float factor = v->elements[0];
    v->elements[0] = 1.0;
    for(size_t i = 1; i < v->size; ++i)
    {
	v->elements[i] = v->elements[i] / factor;
    }
}

extern void vector_sort(vector* v)
{
    assert(v != NULL);
    qsort(v->elements, v->size, sizeof(float), float_comparator);
}

