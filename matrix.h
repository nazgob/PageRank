#ifndef MATRIX_H
#define MATRIX_H

#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix
{
    void** elements;
    size_t element_size;
    size_t dimension;
} matrix;

extern void matrix_init(matrix* m, size_t element_size, size_t dimension);

extern void matrix_free(matrix* m, size_t dimension);

extern void matrix_display(const matrix* m, size_t dimension);

extern void matrix_populate(const matrix* m, size_t dimension);

#endif // MATRIX_H

