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
	mu_run_test(test_vector_copy);
	mu_run_test(test_vector_sort);

	mu_run_test(test_matrix_multiply);
	mu_run_test(test_matrix_transpose);
	mu_run_test(test_matrix_solve);

	mu_run_test(test_gen_web_matrix);
	mu_run_test(test_calculate_links);
	mu_run_test(test_calculate_probability);
	mu_run_test(test_full_algorithm);

	return 0;
}

size_t g_n_threads;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Podaj jako pierwszy argument rozmiar grafu, jako drugi, liczbe watkow.\n");
		return 1;
	}

	size_t web_size = atoi(argv[1]);
	assert(web_size < 10000);
	size_t n_threads = atoi(argv[2]);
	assert(n_threads > 0);

	g_n_threads = n_threads;

	assert(web_size % n_threads == 0);
	
	srand(time(0));

	char* result = all_tests();
	if (result != 0)
	{
		printf("%s\n", result);
	}
	else
	{
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);


	printf("Trwa obliczanie...\n");

	page_rank(web_size);

	return 0;
}

