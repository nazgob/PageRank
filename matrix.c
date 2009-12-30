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
    sprintf(tmp, "%f", *(float*)ptr);
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

extern void matrix_free(matrix* m, size_t dimension)
{
    for (size_t i = 0; i < dimension; ++i)
    {
	free(m->elements[i]);
    }

    free(m->elements);
    m->elements = NULL;
    m = NULL;
}

extern void* matrix_get(const matrix* m, size_t i, size_t j)
{
    void* tmp = ((char*)(m->elements[i]) + m->element_size * j);
    return tmp;
}

extern void matrix_display(const matrix* m, size_t dimension, char*(*pfun)(void* ptr))
{
    for (size_t i = 0; i < dimension; ++i)
    {
	for(size_t j = 0; j < dimension; ++j)
	{
	    printf("|%s| ", pfun(matrix_get(m, i, j)));
	}
	printf("\n");
    }
}

extern void matrix_populate(const matrix* m, size_t dimension)
{
    int tmp = 0;
    int* intp = &tmp;

    for (size_t i = 0; i < dimension; ++i)
    {
	for(size_t j = 0; j < dimension; ++j)
	{
	    *intp = rand() % 2; 
	    void* target = (char*)(matrix_get(m, i, j));
	    memcpy(target, intp, m->element_size);	
	}
    }
}

