#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <matrix.h>
#include <vector.h>
#include <math.h>
#include <mpi.h>

extern size_t calculate_links(const matrix* m, size_t row);

extern float calculate_probability(const matrix* m, size_t i, size_t j);

extern void gen_web_matrix(const matrix* m);

extern void gen_google_matrix(matrix* a, matrix* m);

extern void matrix_solve(vector* v, const matrix* m);

extern void page_rank(size_t size);

#endif // ALGORITHM_H

