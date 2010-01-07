#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <matrix.h>
#include <vector.h>
#include <math.h>

extern size_t number_of_links_coming_from(matrix* m, size_t row);

extern float calculateTransitionProbability(matrix* m, size_t i, size_t j);

extern void matrix_gen(matrix* m, size_t dimension);

extern void gen_a_matrix(matrix* a, matrix* m, size_t dimension);

extern void matrix_solve(vector* v, const matrix* m);

#endif // ALGORITHM_H

