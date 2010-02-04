#include <algorithm.h>

extern size_t calculate_links(const matrix* m, size_t row)
{
	assert(m != NULL);
	assert(row <= m->size);

	size_t counter = 0;
	for (size_t i = 0; i < m->size; ++i)
	{
		counter += m->elements[i][row]; 
	}

	if(counter == 0)
	{
		return m->size;
	}
	assert(counter <= m->size);

	return counter;
}

extern float calculate_probability(const matrix* m, size_t i, size_t j)
{
	assert(m != NULL);
	float p = 1.0;
	size_t r = calculate_links(m, i);

	float a = (p * m->elements[i][j] / r) + ((1 - p) / m->size);

	return a;
}

extern void gen_web_matrix(const matrix* m)
{
	assert (m != NULL);
	for (size_t i = 0; i < m->size; ++i)
	{
		for(size_t j = 0; j < m->size; ++j)
		{
			m->elements[i][j] = rand() % 2;
		}
	}
}

extern void* parallel_calculate(void* _parallel_info)
{
	assert(_parallel_info != NULL);

	parallel_info* info = (parallel_info*)_parallel_info;

	assert(info->in != NULL);
	assert(info->out != NULL);

	size_t n_threads = info->n_threads;

	size_t id = info->id;
	size_t size = info->size;
	size_t slice = size / n_threads;

	assert(size % n_threads == 0);

	for (size_t i = 0; i < size; ++i)
	{
		for(size_t j = slice * id; j < slice * id + slice; ++j)
		{
			info->out->elements[i][j] = calculate_probability(info->in, i, j);
		}
	}

	free(_parallel_info); //_parallel_info has been alocated in gen_google_matrix

	return NULL;
}

extern void gen_google_matrix(matrix* a, matrix* m)
{
	assert(a != 0);
	assert(m != 0);
	assert(a->size == m->size);

	const size_t n_threads = 5;
	pthread_t callThd[n_threads];

	for(size_t x = 0; x < n_threads; ++x)
	{
		parallel_info* info = (parallel_info*)malloc(sizeof(parallel_info));
		info->n_threads = n_threads;
		info->size = a->size;
		info->in = m;
		info->out = a;
		info->id = x;

		int ret = pthread_create(&callThd[x], NULL, parallel_calculate, (void*)info);
		assert(ret == 0);
	}

	int status = 0;
	for(size_t x = 0; x < n_threads; ++x)
	{
		int ret = pthread_join(callThd[x], (void**)&status);
		assert(ret == 0);
		assert(status == 0);
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
		matrix_multiply(&tmp_vec, m, v);

		vector_normalize(&tmp_vec);

		for (size_t i = 0; i < size; ++i)
		{
			v->elements[i] = tmp_vec.elements[i];
			tmp_vec.elements[i] = 0.0;
		}
	}
	vector_free(&tmp_vec);
}

extern void page_rank(size_t size)
{
	matrix w;
	matrix_init(&w, size);
	gen_web_matrix(&w);

	matrix g;
	matrix_init(&g, size);
	gen_google_matrix(&g, &w);

	matrix_free(&w);

	vector p;
	vector_init(&p, size);

	matrix_transpose(&g);

	matrix_solve(&p, &g);

	vector_sort(&p);

	vector_save(&p);
	vector_free(&p);

	matrix_free(&g);
}

