#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <matrix.h>

int main(void)
{
    printf("PRR...\n");

    const int int_size = sizeof(int);
    //const int float_size = sizeof(float);
    //const int double_size = sizeof(double);
    const int dimension = 4;

    srand(time(0));

    matrix m;
    matrix_init(&m, int_size, dimension);

    matrix_populate(&m, dimension);
    matrix_display(&m, dimension);

    matrix_free(&m, dimension);

    return 0;
}

