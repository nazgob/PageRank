#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <matrix.h>
#include <algorithm.h>
#include <minunit.h>
#include <utils.h>
#include <tests.h>

static char* all_tests()
{
    mu_run_test(test_compare_floats);
    mu_run_test(test_vector_normalize);
    mu_run_test(test_algo);
    mu_run_test(test_vector_copy);
    mu_run_test(test_vector_sort);
    mu_run_test(test_no_abstractions);
    mu_run_test(test_old);
    return 0;
}

int main(void)
{
    char *result = all_tests();
    if (result != 0)
    {
	printf("%s\n", result);
    }
    else
    {
	printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return 0;
}

