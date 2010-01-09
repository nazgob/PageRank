#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <utils.h>

typedef struct vector
{
    float* elements;
    size_t size;
} vector;

extern void vector_init(vector* v, size_t size);

extern void vector_free(vector* v);

extern void vector_normalize(vector* v);

extern void vector_sort(vector* v);

extern void vector_display(vector *v);

#endif // VECTOR_H

