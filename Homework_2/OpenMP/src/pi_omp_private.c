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

int main() {
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0 / (double)num_steps;

	start_time = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for reduction(+:sum) private(x)	//Parallel reduces the variable 'sum' by adding every copy generated to the master original 'sum'
		for (i=0; i< num_steps; i++){				//Also, variable 'x' keeps private in every thread generating a copy of the original one.
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	}
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;

	printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi, run_time);

	return 0;
}
