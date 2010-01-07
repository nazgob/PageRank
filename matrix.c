#include <matrix.h>

extern char* cast_int(void* ptr)
{
    assert(ptr != NULL);
    static char tmp[128];
    sprintf(tmp, "%d", *(int*)ptr);
    return tmp;	
}

extern char* cast_float(void* ptr)
{
    assert(ptr != NULL);
    static char tmp[128];
    sprintf(tmp, "%.4f", *(float*)ptr);
    return tmp;	
}

extern void matrix_init(matrix* m, size_t element_size, size_t dimension)
{
    m->element_size = element_size;
    m->dimension = dimension;
    m->elements = (void**)malloc(element_size * dimension);

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

extern void* matrix_get(const matrix* m, size_t i, size_t j)
{
    void* tmp = ((char*)(m->elements[i]) + m->element_size * j); // TODO: static?
    return tmp;
}

extern void matrix_display(const matrix* m, char*(*pfun)(void* ptr))
{
    assert(m != NULL);
    for (size_t i = 0; i < m->dimension; ++i)
    {
	for(size_t j = 0; j < m->dimension; ++j)
	{
	    printf("|%s| ", pfun(matrix_get(m, i, j)));
	}
	printf("\n");
    }
    printf("\n");
}

extern void matrix_populate(const matrix* m)
{
    int tmp = 0;
    int* intp = &tmp;

    for (size_t i = 0; i < m->dimension; ++i)
    {
	for(size_t j = 0; j < m->dimension; ++j)
	{
	    *intp = rand() % 2; 
	    void* target = (char*)(matrix_get(m, i, j));
	    memcpy(target, intp, m->element_size);	
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
	    tmp = *(float*)(matrix_get(m, i, j));
	    *(float*)(matrix_get(m, i, j)) = *(float*)(matrix_get(m, j, i)); 
	    *(float*)(matrix_get(m, j, i)) = tmp;
	}
    }
}

extern void matrix_multiply(matrix* c, const matrix* a, const matrix* b)
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
}


