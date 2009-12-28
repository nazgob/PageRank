#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <matrix.h>

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

