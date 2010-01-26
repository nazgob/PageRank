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

extern void gen_google_matrix(matrix* a, matrix* m)
{
	assert(a != 0);
	assert(m != 0);
	assert(a->size == m->size);

	size_t size = a->size;

	int id = 0;
	int n_threads = 0;
	int tag = 1234;

	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &n_threads);
	MPI_Status status;

	size_t slice = size / n_threads;
	assert (size % n_threads == 0);

	vector tmp;
	vector_init(&tmp, size);

	for (size_t i = 0; i < size; ++i)
	{
		for(size_t j = slice * id; j< slice * id + slice; ++j)
		{
			tmp.elements[j] = calculate_probability(m, i, j);
		}

		if (id != 0)
		{
			int dest = 0;
			MPI_Send(&tmp.elements[slice * id], slice, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
		}
		else
		{
			for (int source = 1; source < n_threads; ++source)
			{
				const size_t max_msg_size = 10000;
				float msg[max_msg_size];
				int res = MPI_Recv(&msg, slice, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
				assert(res == 0);

				for(size_t k = 0; k < slice; ++k)
				{
					a->elements[i][slice * source + k] = msg[k];
				}
				
				for(size_t k = 0; k < slice; ++k)
				{
					a->elements[i][k] = tmp.elements[k];
				}

			}
		}
	}
	
	vector_free(&tmp);
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

	int id = 0;

	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	if(id == 0)
	{
		vector p;
		vector_init(&p, size);

		matrix_transpose(&g);

		matrix_solve(&p, &g);

		vector_sort(&p);

		vector_save(&p);
		vector_free(&p);
	}
	matrix_free(&g);
}

