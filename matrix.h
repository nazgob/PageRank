#ifndef MATRIX_H
#define MATRIX_H

#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix
{
    float** elements;
    size_t element_size;
    size_t dimension;
} matrix;

extern void matrix_init(matrix* m, size_t element_size, size_t dimension);

extern void matrix_free(matrix* m);

extern float matrix_get(const matrix* m, size_t i, size_t j);

extern void matrix_display(const matrix* m);

extern void matrix_populate(const matrix* m);

extern void matrix_transpose(const matrix* m);

//extern void matrix_multiply(matrix* c, const matrix* a, const matrix* b);

#endif // MATRIX_H

