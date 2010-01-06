#ifndef TESTS_H
#define TESTS_H

#include <vector.h>
#include <algorithm.h>

int tests_run = 0;

static char* test_vector_sort()
{
    float v[3] = {1.5, -0.5, 0.8};
    vector_sort(v, 3);

    mu_assert("vector_sort failed", compare_floats(v[0], -0.5));
    mu_assert("vector_sort failed", compare_floats(v[1], 0.8));
    mu_assert("vector_sort failed", compare_floats(v[2], 1.5));

    return 0;
}

static char* test_compare_floats()
{
    mu_assert("compare_floats failed", compare_floats(0.0, 0.0));
    mu_assert("compare_floats failed", compare_floats(0.001, 0.001));
    mu_assert("compare_floats failed", !compare_floats(0.0, 0.0150));
    return 0;
}

static char* test_vector_copy()
{
    const size_t dimension = 3;
    float* vec = (void*)malloc(sizeof(float) * dimension);
    float* tmp_vec = (void*)malloc(sizeof(float) * dimension);


    for (size_t i = 0; i < dimension; ++i)
    {
	vec[i] = 0.0;
	tmp_vec[i] = 6.66;
    }

    for (size_t i = 0; i < dimension; ++i)
    {
	mu_assert("vector init failed", compare_floats(vec[i], 0.0));
	mu_assert("vector init failed", compare_floats(tmp_vec[i], 6.66));
    }

    for (size_t i = 0; i < dimension; ++i)
    {
	vec[i] = tmp_vec[i];
	tmp_vec[i] = 0.0;
    }

    for (size_t i = 0; i < dimension; ++i)
    {
	mu_assert("vector copy failed", compare_floats(vec[i], 6.66));
	mu_assert("vector copy failed", compare_floats(tmp_vec[i], 0.0));
    }

    free(vec);
    free(tmp_vec);

    return 0;
}

static char* test_vector_normalize()
{
    float v[3] = {2.5, -0.5, -0.5};
    vector_normalize(v, 3);
    mu_assert("vector_normalize failed", v[0] == 1.0);
    mu_assert("vector_normalize failed", compare_floats(v[1], -0.2));
    mu_assert("vector_normalize failed", compare_floats(v[2], -0.2));

    return 0;
}

static char* test_algo()
{
    matrix sample;
    matrix_init(&sample, sizeof(float), 3);

    matrix_multiply_by_vec(&sample, 3);
    //matrix_display(&sample, 3, cast_float);

    matrix_free(&sample, 3);
    return 0;
}

static char* test_old()
{
    const int dimension = 5;
    srand(time(0));

    matrix m;
    matrix_gen(&m, dimension);

    printf("\n");

    matrix a;
    gen_a_matrix(&a, &m, dimension);
    matrix_display(&a, dimension, cast_float);

    matrix_transpose(&a, dimension);
    matrix_display(&a, dimension, cast_float);

    matrix x;
    matrix_multiply(&x, &a, &m, dimension);
    matrix_display(&x, dimension, cast_float);


    matrix sample;
    matrix_init(&sample, sizeof(float), 3);

    matrix_multiply_by_vec(&sample, 3);
    //matrix_display(&sample, 3, cast_float);

    matrix_free(&sample, 3);

    matrix_free(&a, dimension);
    matrix_free(&m, dimension);
    matrix_free(&x, dimension);

    return 0;
}

#endif // TESTS_H

