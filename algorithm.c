#include <algorithm.h>

extern size_t number_of_links_coming_from(matrix* m, size_t row)
{
    assert(m != NULL);

    size_t counter = 0;
    for (size_t i = 0; i < m->dimension; ++i)
    {
	counter += *(int*)(matrix_get(m, row, i));
    }
    assert(counter <= m->dimension);

    return counter;
}

extern float calculateTransitionProbability(matrix* m, size_t i, size_t j)
{
    assert(m != NULL);
    float p = 0.85;
    size_t r = number_of_links_coming_from(m, i);
    (r == 0) ? r = 1 : r; // when page has no links...

    int tmp = *(int*)(matrix_get(m, i, j));

    float a = ((p * tmp / r) + (1 - p)) / pow(m->dimension, 2);

    return a;
}

extern void matrix_gen(matrix* m, size_t dimension)
{
    matrix_init(m, sizeof(int), dimension);
    matrix_populate(m);
    char*(*pfun)(void* ptr) = cast_int;
    matrix_display(m, pfun);
}

extern void gen_a_matrix(matrix* a, matrix* m, size_t dimension)
{
    matrix_init(a, sizeof(float), dimension);

    float tmp = 0.0;
    float* floatp= &tmp;

    for (size_t i = 0; i < dimension; ++i)
    {
	for(size_t j = 0; j < dimension; ++j)
	{
	    *floatp = calculateTransitionProbability(m, i, j);
	    void* target = (char*)(matrix_get(a, i, j));
	    memcpy(target, floatp, a->element_size);	
	}
    }
    //char*(*pfun)(void* ptr) = cast_float;
    //matrix_display(a, dimension, pfun);
}

extern void matrix_solve(vector* v, const matrix* m)
{
    assert(m != NULL);

    size_t size = m->dimension;

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
		tmp_vec.elements[i] += (*(float*)(matrix_get(m, i, j))) * v->elements[j]; 
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

