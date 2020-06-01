/*
	This file is for testing the project.c and project.h files
*/

#include "project.h"

int main()
{
    clock_t t;
    t = clock();

    srand(time(0));
    int repeats;
    int results[10];
    int population=2000;
    int infected=5;
    double serviceProvider=0.03;
    double spinteraction=0.05;
    int normal_interactions100=6;
    int normal_interactions50;
    int normal_interactions33;

    doExperiment(population, serviceProvider, spinteraction, infected, normal_interactions100, 1);

    printf("************************************************************************************************************************************ \n");
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("TIME TAKEN: %f seconds. \n", time_taken);
    return 0;
}
