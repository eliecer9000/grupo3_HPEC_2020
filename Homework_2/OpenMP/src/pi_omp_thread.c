/*
 * pi.c
 *
 *  Created on: Aug 18, 2020
 *      Author: project2
 */

#include <omp.h>
#include <stdio.h>
static long num_steps = 100000000;
double step;
void paralelo(int n);

int main() {
	int nthreads;

	for (nthreads=1; nthreads<= 4; nthreads++){	//Increase amount of threads running
		paralelo(nthreads);
	}

	return 0;
}

void paralelo(int n){
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0 / (double)num_steps;
	start_time = omp_get_wtime();
	#pragma omp parallel num_threads(n)	//Definition of the threads running
	{
		#pragma omp parallel for reduction(+:sum)	//Parallel reduces the variable 'sum' by adding every copy generated to the master original 'sum'
		for (i=0; i< num_steps; i++){
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	}
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("pi with %d Threads is %lf in %lf seconds\n", n, pi, run_time);

}
