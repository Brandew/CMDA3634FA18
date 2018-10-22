#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char **argv){
	int i = 350;
	int sum = 0;
	#pragma omp parallel num_threads(10)
	{
		int rank = omp_get_thread_num();
		int size = omp_get_num_threads();
		int tmp = sum;
		tmp = tmp+1;
		sum = tmp;

		printf("hello worldfrom OpenMP thread %d out of %d\n",
			       	rank,size);
		//printf("the sum is %d\n", sum);

		printf("thread %d got i = %d\n",rank,i);
	}

	printf("the sum is %d\n", sum);

	#pragma omp parallel num_threads(5)
        {
                printf("goodbye cruel world\n");
        }

}
