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
    size_t size;
} matrix;

extern void matrix_init(matrix* m, size_t size);

extern void matrix_free(matrix* m);

extern void matrix_display(const matrix* m);

extern void matrix_transpose(const matrix* m);

//extern void matrix_multiply(matrix* c, const matrix* a, const matrix* b);

#endif // MATRIX_H

