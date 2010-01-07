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

static char* test_matrix_solve()
{
    size_t problem_size = 3;
    matrix problem;

    matrix_init(&problem, sizeof(float), problem_size);
    
    *(float*)(matrix_get(&problem, 0, 0)) = 1.5;
    *(float*)(matrix_get(&problem, 0, 1)) = 0.0;
    *(float*)(matrix_get(&problem, 0, 2)) = 1.0;
    *(float*)(matrix_get(&problem, 1, 0)) = -0.5;
    *(float*)(matrix_get(&problem, 1, 1)) = 0.5;
    *(float*)(matrix_get(&problem, 1, 2)) = -0.5;
    *(float*)(matrix_get(&problem, 2, 0)) = -0.5;
    *(float*)(matrix_get(&problem, 2, 1)) = 0.0;
    *(float*)(matrix_get(&problem, 2, 2)) = 0.0;

    vector v;
    vector_init(&v, problem_size);
    matrix_solve(&v, &problem);

    for (size_t i = 0; i < problem_size; ++i)
    {
	printf("* %f *, ", v.elements[i]);
    }
    printf("\n");

    mu_assert("matrix_solve failed", compare_floats(v.elements[0], 1.0));
    mu_assert("matrix_solve failed", compare_floats(v.elements[1], -0.44));
    mu_assert("matrix_solve failed", compare_floats(v.elements[2], -0.44));
    
    matrix_free(&problem);
    vector_free(&v);

    return 0;
}

static char* test_no_abstractions()
{
    // test vector
    typedef struct vector
    {
	float* elements;
	size_t size;
    } vector;

    vector v;
    v.size = 3;
    v.elements = (float*)malloc(sizeof(float) * v.size);
    for(size_t i = 0; i < v.size; ++i)
    {
	v.elements[i] = i * 0.1;
    }

    mu_assert("no abstraction failed", compare_floats(v.elements[0], 0.0));
    mu_assert("no abstraction failed", compare_floats(v.elements[1], 0.1));
    mu_assert("no abstraction failed", compare_floats(v.elements[2], 0.2));

    free(v.elements);

    // test matrix2
    typedef struct matrix2
    {
	float** elements;
	size_t size;
    } matrix2;


    matrix2 m2;
    m2.size = 3;
    m2.elements = (float**)malloc(sizeof(float) * m2.size);
    for(size_t i = 0; i < m2.size; ++i)
    {
	m2.elements[i] = (float*)malloc(sizeof(float) * m2.size);
    }

    size_t tmp = 0.0;

    for(size_t i = 0; i < m2.size; ++i)
    {
	for (size_t j = 0; j < m2.size; ++j)
	{
	    m2.elements[i][j] = tmp;
	    tmp++;
	}
    }

    mu_assert("no abstraction failed", compare_floats(m2.elements[0][0], 0.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[0][1], 1.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[0][2], 2.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[1][0], 3.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[1][1], 4.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[1][2], 5.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[2][0], 6.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[2][1], 7.0));
    mu_assert("no abstraction failed", compare_floats(m2.elements[2][2], 8.0));

    for(size_t i = 0; i < m2.size; ++i)
    {
	free(m2.elements[i]);
    }
    free(m2.elements);

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
    matrix_display(&a, cast_float);

    matrix_transpose(&a);
    matrix_display(&a, cast_float);

    matrix x;
    matrix_multiply(&x, &a, &m);
    matrix_display(&x, cast_float);


    matrix sample;
    matrix_init(&sample, sizeof(float), 3);

    vector v;
    vector_init(&v, dimension);
    matrix_solve(&v, &sample);

    matrix_free(&sample);

    matrix_free(&a);
    matrix_free(&m);
    matrix_free(&x);

    vector_free(&v);

    return 0;
}

#endif // TESTS_H

