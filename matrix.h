#ifndef MATRIX_H
#define MATRIX_H

#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* cast_int(void* ptr);

extern char* cast_float(void* ptr);

typedef struct matrix
{
    void** elements;
    size_t element_size;
    size_t dimension;
} matrix;

extern void matrix_init(matrix* m, size_t element_size, size_t dimension);

extern void matrix_free(matrix* m);

extern void* matrix_get(const matrix* m, size_t i, size_t j);

extern void matrix_display(const matrix* m, char*(*pfun)(void* ptr));

extern void matrix_populate(const matrix* m);

extern void matrix_transpose(const matrix* m);

extern void matrix_multiply(matrix* c, const matrix* a, const matrix* b);

#endif // MATRIX_H

