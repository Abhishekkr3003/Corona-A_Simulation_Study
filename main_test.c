#include "project.h"

int main()
{
    clock_t t;
    t = clock();

    srand(time(0));
    int repeats;
    int results[10];
    int population=10000;
    int infected=100;
    double serviceProvider=0.03;
    double spinteraction=0.05;
    int normal_interactions100=6;
    int normal_interactions50;
    int normal_interactions33;

    doExperiment(population, serviceProvider, spinteraction, infected, normal_interactions100, 1);

    // for(int i=0;i<population;i++)
    // {
    //     int row_count=0;
    //     for(int j=0;j<population;j++)
    //     {
    //         if(town[i][j]==1)
    //             row_count++;
    //     }
    //     printf("Row %d: %d\n", i+1, row_count);
    // }
    printf("************************************************************************************************************************************ \n");
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("TIME TAKEN: %f seconds. \n", time_taken);
    return 0;
}