#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <matrix.h>
#include <vector.h>
#include <math.h>

extern size_t number_of_links_coming_from(matrix* m, size_t row, size_t dimension);

extern float calculateTransitionProbability(matrix* m, size_t i, size_t j, size_t dimension);

extern void matrix_gen(matrix* m, size_t dimension);

extern void gen_a_matrix(matrix* a, matrix* m, size_t dimension);

extern void matrix_multiply_by_vec(const matrix* m, size_t dimension);

#endif // ALGORITHM_H

