#include <matrix.h>

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

extern void matrix_display(const matrix* m, size_t dimension)
{
    for (size_t i = 0; i < dimension; ++i)
    {
	for(size_t j = 0; j < dimension; ++j)
	{
	    printf("%d ", *(int*)((char*)(m->elements[i]) + 4 * j));
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
	    void* target = (char*)(m->elements[i]) + 4 * j;
	    memcpy(target, intp, 4);	
	}
    }
}

