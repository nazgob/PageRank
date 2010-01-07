#ifndef TESTS_H
#define TESTS_H

#include <vector.h>
#include <algorithm.h>

int tests_run = 0;

static char* test_vector_sort()
{
    vector v;
    vector_init(&v, 3);

    v.elements[0] = 1.5;
    v.elements[1] = -0.5;
    v.elements[2] = 0.8;

    vector_sort(&v);

    mu_assert("vector_sort failed", compare_floats(v.elements[0], -0.5));
    mu_assert("vector_sort failed", compare_floats(v.elements[1], 0.8));
    mu_assert("vector_sort failed", compare_floats(v.elements[2], 1.5));

    vector_free(&v);

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
    size_t size = 3;

    vector vec;
    vector_init(&vec, size);

    vector tmp_vec;
    vector_init(&tmp_vec, size);

    for (size_t i = 0; i < size; ++i)
    {
	vec.elements[i] = 0.0;
	tmp_vec.elements[i] = 6.66;
    }

    for (size_t i = 0; i < size; ++i)
    {
	mu_assert("vector init failed", compare_floats(vec.elements[i], 0.0));
	mu_assert("vector init failed", compare_floats(tmp_vec.elements[i], 6.66));
    }

    for (size_t i = 0; i < size; ++i)
    {
	vec.elements[i] = tmp_vec.elements[i];
	tmp_vec.elements[i] = 0.0;
    }

    for (size_t i = 0; i < size; ++i)
    {
	mu_assert("vector copy failed", compare_floats(vec.elements[i], 6.66));
	mu_assert("vector copy failed", compare_floats(tmp_vec.elements[i], 0.0));
    }

    vector_free(&vec);
    vector_free(&tmp_vec);

    return 0;
}

static char* test_vector_normalize()
{
    vector v;
    vector_init(&v, 3);

    v.elements[0] = 2.5;
    v.elements[1] = -0.5;
    v.elements[2] = -0.5;

    vector_normalize(&v);

    mu_assert("vector_normalize failed", compare_floats(v.elements[0], 1.0));
    mu_assert("vector_normalize failed", compare_floats(v.elements[1], -0.2));
    mu_assert("vector_normalize failed", compare_floats(v.elements[2], -0.2));

    vector_free(&v);

    return 0;
}

static char* test_matrix_transpose()
{
    size_t problem_size = 2;
    matrix problem;

    matrix_init(&problem, problem_size);

    problem.elements[0][0] = 1.0;
    problem.elements[0][1] = 2.0;
    problem.elements[1][0] = 3.0;
    problem.elements[1][1] = 4.0;

    matrix_transpose(&problem);

    mu_assert("matrix_tranpose failed", compare_floats(problem.elements[0][0], 1.0));
    mu_assert("matrix_tranpose failed", compare_floats(problem.elements[0][1], 3.0));
    mu_assert("matrix_tranpose failed", compare_floats(problem.elements[1][0], 2.0));
    mu_assert("matrix_tranpose failed", compare_floats(problem.elements[1][1], 4.0));
    
    matrix_free(&problem);

    return 0;
}
    
static char* test_matrix_solve()
{
    size_t problem_size = 3;
    matrix problem;

    matrix_init(&problem, problem_size);

    problem.elements[0][0] = 1.5;
    problem.elements[0][1] = 0.0;
    problem.elements[0][2] = 1.0;
    problem.elements[1][0] = -0.5;
    problem.elements[1][1] = 0.5;
    problem.elements[1][2] = -0.5;
    problem.elements[2][0] = -0.5;
    problem.elements[2][1] = 0.0;
    problem.elements[2][2] = 0.0;

    vector v;
    vector_init(&v, problem_size);
    matrix_solve(&v, &problem);

    mu_assert("matrix_solve failed", compare_floats(v.elements[0], 1.0));
    mu_assert("matrix_solve failed", compare_floats(v.elements[1], -0.44));
    mu_assert("matrix_solve failed", compare_floats(v.elements[2], -0.44));

    matrix_free(&problem);
    vector_free(&v);

    return 0;
}

static char* test_full_algorithm()
{
    size_t web_size = 10;

    matrix w;
    matrix_init(&w, web_size);
    gen_web_matrix(&w); // random generated links matrix

    matrix g;
    matrix_init(&g, web_size);
    gen_google_matrix(&g, &w);

    vector p;
    vector_init(&p, web_size);

    matrix_transpose(&g);
    matrix_solve(&p, &g);

    vector_sort(&p);

    for (size_t i = 0; i < web_size; ++i)
    {
	printf("PageRank = %f\n", p.elements[i]);
    }

    matrix_free(&w);
    matrix_free(&g);
    vector_free(&p);

    return 0;
}

#endif // TESTS_H

