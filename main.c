#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <matrix.h>

void matrix_populate(const matrix* m, size_t dimension)
{
    int tmp = 0;
    int* intp = &tmp;

    for (size_t i = 0; i < dimension; ++i)
    {
	for(size_t j = 0; j < dimension; ++j)
	{
	    (*intp)++; 
	    void* target = (char*)(m->elements[i]) + 4 * j;
	    memcpy(target, intp, 4);	
	}
    }
}

int main(void)
{
    printf("PRR...\n");
    printf("sizeof(int) = %d \n", sizeof(int));
    printf("sizeof(float) = %d \n", sizeof(float));
    printf("sizeof(double) = %d \n", sizeof(double));

    const int int_size = 4;
    //const int float_size = 4;
    //const int double_size = 8;
    const int dimension = 4;

    srand(time(0));

    matrix m;
    matrix_init(&m, int_size, dimension);

    matrix_populate(&m, dimension);
    matrix_display(&m, dimension);

    matrix_free(&m, dimension);

    return 0;
}

