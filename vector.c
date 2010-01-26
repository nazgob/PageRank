#include <vector.h>

extern void vector_init(vector* v, size_t size)
{
	assert(size > 0);
	v->size = size;
	v->elements = (float*)malloc(sizeof(float) * v->size);
}

extern void vector_free(vector* v)
{
	assert(v != NULL);
	free(v->elements);
	v->elements = NULL;
	v->size = 0;
	v = NULL;
}

extern void vector_normalize(vector* v)
{
	assert(v != NULL);

	float sum = 0.0;
	for (size_t i = 0; i < v->size; ++i)
	{
		sum += v->elements[i];
	}
	for (size_t i = 0; i < v->size; ++i)
	{
		v->elements[i] /= sum;
	}
}

extern void vector_sort(vector* v)
{
	assert(v != NULL);
	qsort(v->elements, v->size, sizeof(float), float_comparator);
}

extern void vector_display(vector* v) 
{
	assert (v != NULL);
	for (size_t i = 0; i < v->size; ++i)
	{
		printf("|%.4f| \n", v->elements[i]);
	}
}

extern void vector_save(const vector* v)
{
	assert (v != NULL);

	FILE *fp = NULL;
	fp = fopen("page_rank.txt", "wb");

	if(fp == NULL)
	{
		printf("IO error.\n");
		return;
	}

	float sum = 0.0;
	for (size_t i = 0; i < v->size; ++i)
	{
		fprintf(fp, "|%.8f| \n", v->elements[i]);
		sum += v->elements[i];
	}

	fprintf(fp, "sum = %f\n", sum);

	printf("Wyniki zapisano w pliku page_rank.txt\n");
	fclose(fp);
}

