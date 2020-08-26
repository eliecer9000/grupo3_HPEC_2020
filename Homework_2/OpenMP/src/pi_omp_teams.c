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
	#pragma omp target		//Teams constructs require target directive
	{
		#pragma omp teams num_teams(3) thread_limit(3) reduction(+:sum)	//It is defined 3 teams with a maximum of 3 threads
		#pragma omp distribute	//distribute the next for loop
		for (i=0; i< num_steps; i++){
			x = (i+0.5)*step;
			sum = sum + 4.0/(1.0+x*x);
		}
	}
	pi = step * sum;
	run_time = omp_get_wtime() - start_time;

	printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi, run_time);

	return 0;
}