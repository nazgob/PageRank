#include <matrix.h>

/*extern char* cast_float(void* ptr)
{
    assert(ptr != NULL);
    static char tmp[128];
    sprintf(tmp, "%.4f", *(float*)ptr);
    return tmp;	
}*/

extern void matrix_init(matrix* m, size_t element_size, size_t dimension)
{
    m->element_size = element_size;
    m->dimension = dimension;
    m->elements = (float**)malloc(element_size * dimension);

    assert(m->elements != NULL);

    for (size_t i = 0; i < dimension; ++i)
    {
	m->elements[i] = malloc(element_size * dimension);
    }
}

extern void matrix_free(matrix* m)
{
    assert(m != NULL);
    for (size_t i = 0; i < m->dimension; ++i)
    {
	free(m->elements[i]);
    }

    free(m->elements);
    m->elements = NULL;
    m->dimension = 0;
    m->element_size = 0;
    m = NULL;
}

extern float matrix_get(const matrix* m, size_t i, size_t j)
{
    float tmp = m->elements[i][j];//((char*)(m->elements[i]) + m->element_size * j); // TODO: static?
    return tmp;
}

extern void matrix_display(const matrix* m)
{
    assert(m != NULL);
    for (size_t i = 0; i < m->dimension; ++i)
    {
	for(size_t j = 0; j < m->dimension; ++j)
	{
	    printf("|%.4f| ", m->elements[i][j]);// matrix_get(m, i, j));
	}
	printf("\n");
    }
    printf("\n");
}

extern void matrix_populate(const matrix* m)
{
    for (size_t i = 0; i < m->dimension; ++i)
    {
	for(size_t j = 0; j < m->dimension; ++j)
	{
	    m->elements[i][j] = rand() % 2;
	}
    }
}

extern void matrix_transpose(const matrix* m)
{
    assert(m != NULL);
    float tmp = 0.0;

    for (size_t i = 0; i < m->dimension; ++i)
    {
	for (size_t j = i+1; j < m->dimension; ++j)
	{
	    tmp = m->elements[i][j];
	    m->elements[i][j] = m->elements[j][i];
	    m->elements[j][i] = tmp;

	    /*tmp = *(float*)(matrix_get(m, i, j));
	    *(float*)(matrix_get(m, i, j)) = *(float*)(matrix_get(m, j, i)); 
	    *(float*)(matrix_get(m, j, i)) = tmp;*/
	}
    }
}

/*extern void matrix_multiply(matrix* c, const matrix* a, const matrix* b)
{
    assert(a != NULL);
    assert(b != NULL);

    matrix_init(c, sizeof(float), a->dimension);

    for (size_t i = 0; i < a->dimension; ++i)
    {
	for (size_t j = 0; j < a->dimension; ++j)
	{
	    *(float*)(matrix_get(c, i, j)) = 0;
	    for (size_t k = 0; k < a->dimension; ++k)
	    {
		*(float*)(matrix_get(c, i, j)) += (*(float*)(matrix_get(a, i, k))) * (*(int*)(matrix_get(b, k, j))); 
		//printf("%f-%d-%d ", (*(float*)(matrix_get(b, k, j))), i, k);
	    }
	}
    }
}*/


