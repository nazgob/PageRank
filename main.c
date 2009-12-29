#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <matrix.h>

void matrix_gen(matrix* m, size_t dimension)
{
    matrix_init(m, sizeof(int), dimension);
    matrix_populate(m, dimension);
    matrix_display(m, dimension);
}

size_t number_of_links_coming_from(matrix* m, size_t row, size_t dimension)
{
    assert(m != NULL);

    size_t counter = 0;
    for (size_t i = 0; i < dimension; ++i)
    {
	counter += *(int*)(matrix_get(m, row, i));
    }

    return counter;
}

float calculateTransitionProbability(matrix* m, size_t i, size_t j, size_t dimension)
{
    float p = 0.85;
    size_t r = number_of_links_coming_from(m, i, dimension);

    int tmp = *(int*)(matrix_get(m, i, j));

    float a = ((p * tmp / r) + (1 - p)) / pow(dimension, 2);

    return a;
}

int main(void)
{
    printf("PRR...\n");

    const int dimension = 4;

    srand(time(0));

    matrix m;
    matrix_gen(&m, dimension);

    size_t score1 = number_of_links_coming_from(&m, 0, dimension);
    printf("score1 = %d\n", score1);

    float score2 = calculateTransitionProbability(&m, 0, 0, dimension);
    printf("score2 = %f\n", score2);

    int* intp = (int*)(matrix_get(&m, 0, 0));
    printf("matrix_get() = %d\n", *intp);

    matrix_free(&m, dimension);

    return 0;
}

