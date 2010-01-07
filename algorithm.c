#include <algorithm.h>

extern size_t number_of_links_coming_from(matrix* m, size_t row, size_t dimension)
{
    assert(m != NULL);

    size_t counter = 0;
    for (size_t i = 0; i < dimension; ++i)
    {
	counter += *(int*)(matrix_get(m, row, i));
    }
    assert(counter <= dimension);

    return counter;
}

extern float calculateTransitionProbability(matrix* m, size_t i, size_t j, size_t dimension)
{
    assert(m != NULL);
    float p = 0.85;
    size_t r = number_of_links_coming_from(m, i, dimension);
    (r == 0) ? r = 1 : r; // when page has no links...

    int tmp = *(int*)(matrix_get(m, i, j));

    float a = ((p * tmp / r) + (1 - p)) / pow(dimension, 2);

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
	    *floatp = calculateTransitionProbability(m, i, j, dimension);
	    void* target = (char*)(matrix_get(a, i, j));
	    memcpy(target, floatp, a->element_size);	
	}
    }
    //char*(*pfun)(void* ptr) = cast_float;
    //matrix_display(a, dimension, pfun);
}

extern void matrix_multiply_by_vec(const matrix* m, size_t dimension)
{
    assert(m != NULL);
    *(float*)(matrix_get(m, 0, 0)) = 1.5;
    *(float*)(matrix_get(m, 0, 1)) = 0.0;
    *(float*)(matrix_get(m, 0, 2)) = 1.0;
    *(float*)(matrix_get(m, 1, 0)) = -0.5;
    *(float*)(matrix_get(m, 1, 1)) = 0.5;
    *(float*)(matrix_get(m, 1, 2)) = -0.5;
    *(float*)(matrix_get(m, 2, 0)) = -0.5;
    *(float*)(matrix_get(m, 2, 1)) = 0.0;
    *(float*)(matrix_get(m, 2, 2)) = 0.0;

    float* vec = (void*)malloc(sizeof(float) * dimension);
    float* tmp_vec = (void*)malloc(sizeof(float) * dimension);

    for (size_t i = 0; i < dimension; ++i)
    {
	vec[i] = 1.0;
	tmp_vec[i] = 0.0;
    }

    for(size_t x = 0; x < 3; ++x)
    {
	printf("\n");
	for (size_t i = 0; i < dimension; ++i)
	{
	    for (size_t j = 0; j < dimension; ++j)
	    {
		//printf("m(m, i, j) = %f * vec[i] = %f\n",  (*(float*)(matrix_get(m, i, j))), vec[i]);
		tmp_vec[i] += (*(float*)(matrix_get(m, i, j))) * vec[j]; 
	    }
	    //printf("\n");
	}

	for(size_t i = 0; i < dimension; ++i)
	{
	    printf("p = %.4f ", tmp_vec[i]);
	}
	printf("\n");
	vector_normalize(tmp_vec, dimension);
	for(size_t i = 0; i < dimension; ++i)
	{
	    printf("n = %.4f ", tmp_vec[i]);
	}
	printf("\n");

	for (size_t i = 0; i < dimension; ++i)
	{
	    vec[i] = tmp_vec[i];
	    tmp_vec[i] = 0.0;
	}
    }
}

