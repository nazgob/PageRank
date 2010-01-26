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

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);

	//g_argc = argc;
	//g_argv = (char**)malloc(sizeof(char*) * argc);
	///for(int i = 0; i < argc; ++i)
	//{
	//	g_argv[i] = (char*)malloc(sizeof(char) * (strlen(argv[i] + 1)));
	//	strncpy(g_argv[i], argv[i], sizeof(g_argv[i]) + 1);
	//}
	//
	if(argc != 2)
	{
		printf("Podaj jako jedyny argument rozmiar grafu.\n");
		return 1;
	}

	size_t web_size = atof(argv[1]);
	assert(web_size < 10000);

	srand(time(0));

	/*char* result = all_tests();
	  if (result != 0)
	  {
	  printf("%s\n", result);
	  }
	  else
	  {
	  printf("ALL TESTS PASSED\n");
	  }
	  printf("Tests run: %d\n", tests_run);*/


	int id = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	if(id == 0)
	{
		printf("Trwa obliczanie...\n");
	}

	page_rank(web_size);

	MPI_Finalize();
	return 0;
}

