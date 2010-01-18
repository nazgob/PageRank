#include <matrix.h>

extern void matrix_init(matrix* m, size_t size)
{
	m->size = size;
	m->elements = (float**)malloc(sizeof(float*) * size);

	assert(m->elements != NULL);

	for (size_t i = 0; i < size; ++i)
	{
		m->elements[i] = malloc(sizeof(float) * size);
	}
}

extern void matrix_free(matrix* m)
{
	assert(m != NULL);
	for (size_t i = 0; i < m->size; ++i)
	{
		free(m->elements[i]);
	}

	free(m->elements);
	m->elements = NULL;
	m->size = 0;
	m = NULL;
}

extern void matrix_display(const matrix* m)
{
	assert(m != NULL);
	for (size_t i = 0; i < m->size; ++i)
	{
		for(size_t j = 0; j < m->size; ++j)
		{
			printf("|%.4f| ", m->elements[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

extern void matrix_transpose(const matrix* m)
{
	assert(m != NULL);
	float tmp = 0.0;

	for (size_t i = 0; i < m->size; ++i)
	{
		for (size_t j = i+1; j < m->size; ++j)
		{
			tmp = m->elements[i][j];
			m->elements[i][j] = m->elements[j][i];
			m->elements[j][i] = tmp;
		}
	}
}

extern void matrix_multiply(vector* tmp, const matrix* m, vector* v)
{
	assert(tmp != NULL);
	assert (m != NULL);
	assert(v!= NULL);
	assert(tmp->size == v->size);
	assert(m->size == v->size);

	size_t size = tmp->size;

	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			tmp->elements[i] += m->elements[i][j] * v->elements[j]; 
		}
	}
}

