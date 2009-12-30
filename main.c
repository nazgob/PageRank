#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <matrix.h>

size_t number_of_links_coming_from(matrix* m, size_t row, size_t dimension)
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

float calculateTransitionProbability(matrix* m, size_t i, size_t j, size_t dimension)
{
    assert(m != NULL);
    float p = 0.85;
    size_t r = number_of_links_coming_from(m, i, dimension);
    (r == 0) ? r = 1 : r; // when page has no links...

    int tmp = *(int*)(matrix_get(m, i, j));

    float a = ((p * tmp / r) + (1 - p)) / pow(dimension, 2);

    return a;
}

void matrix_gen(matrix* m, size_t dimension)
{
    matrix_init(m, sizeof(int), dimension);
    matrix_populate(m, dimension);
    char*(*pfun)(void* ptr) = cast_int;
    matrix_display(m, dimension, pfun);
}

void gen_a_matrix(matrix* a, matrix* m, size_t dimension)
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
    char*(*pfun)(void* ptr) = cast_float;
    matrix_display(a, dimension, pfun);
}

int main(void)
{
    printf("PRR...\n");

    const int dimension = 4;

    srand(time(0));

    matrix m;
    matrix_gen(&m, dimension);

    printf("\n");

    matrix a;
    gen_a_matrix(&a, &m, dimension);

    matrix_free(&a, dimension);
    matrix_free(&m, dimension);

    return 0;
}

