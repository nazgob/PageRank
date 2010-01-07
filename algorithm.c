#include <algorithm.h>

extern size_t number_of_links_coming_from(matrix* m, size_t row)
{
    assert(m != NULL);

    size_t counter = 0;
    for (size_t i = 0; i < m->size; ++i)
    {
	counter += m->elements[row][i]; 
    }
    assert(counter <= m->size);

    return counter;
}

extern float calculateTransitionProbability(matrix* m, size_t i, size_t j)
{
    assert(m != NULL);
    float p = 0.85;
    size_t r = number_of_links_coming_from(m, i);
    (r == 0) ? r = 1 : r; // when page has no links...

    float tmp = m->elements[i][j];

    float a = ((p * tmp / r) + (1 - p)) / pow(m->size, 2);

    return a;
}

extern void gen_web_matrix(const matrix* m)
{
    for (size_t i = 0; i < m->size; ++i)
    {
	for(size_t j = 0; j < m->size; ++j)
	{
	    m->elements[i][j] = rand() % 2;
	}
    }
}

extern void gen_google_matrix(matrix* a, matrix* m)
{
    assert(a != 0);
    assert(m != 0);
    assert(a->size == m->size);

    for (size_t i = 0; i < a->size; ++i)
    {
	for(size_t j = 0; j < a->size; ++j)
	{
	    a->elements[i][j] = calculateTransitionProbability(m, i, j);
	}
    }
}

extern void matrix_solve(vector* v, const matrix* m)
{
    assert(v != NULL);
    assert(m != NULL);
    assert(v->size == m->size);

    size_t size = m->size;

    vector tmp_vec;
    vector_init(&tmp_vec, size);

    for (size_t i = 0; i < size; ++i)
    {
	v->elements[i] = 1.0;
	tmp_vec.elements[i] = 0.0;
    }

    for(size_t x = 0; x < 3; ++x)
    {
	printf("\n");
	for (size_t i = 0; i < size; ++i)
	{
	    for (size_t j = 0; j < size; ++j)
	    {
		tmp_vec.elements[i] += m->elements[i][j] * v->elements[j]; 
	    }
	}

	for(size_t i = 0; i < size; ++i)
	{
	    printf("p = %.4f ", tmp_vec.elements[i]);
	}

	printf("\n");

	vector_normalize(&tmp_vec);

	for(size_t i = 0; i < size; ++i)
	{
	    printf("n = %.4f ", tmp_vec.elements[i]);
	}
	printf("\n");

	for (size_t i = 0; i < size; ++i)
	{
	    v->elements[i] = tmp_vec.elements[i];
	    tmp_vec.elements[i] = 0.0;
	}
    }
    vector_free(&tmp_vec);
}

