#include "project.h"

int main()
{
    clock_t t;
    t = clock();

    srand(time(0));
    int repeats;
    int results[10];
    int population;
    int infected;
    double serviceProvider;
    double spinteraction;
    int normal_interactions100;
    int normal_interactions50;
    int normal_interactions33;
    FILE *fp;
    fp=fopen("Our Result.txt", "w");

    for (int x = 0; x < 4; x++)
    {
        switch (x)
        {
        case 0:
            population = 2000;
            infected = 5;
            serviceProvider = 0.03;
            spinteraction = 0.05;
            normal_interactions100 = 20;
            break;
        case 1:
            population = 2000;
            infected = 100;
            serviceProvider = 0.08;
            spinteraction = 0.03;
            normal_interactions100 = 20;
            break;
        case 2:
            population = 5000;
            infected = 30;
            serviceProvider = 0.03;
            spinteraction = 0.05;
            normal_interactions100 = 20;
            break;
        case 3:
            population = 10000;
            infected = 5;
            serviceProvider = 0.03;
            spinteraction = 0.05;
            normal_interactions100 = 20;
            break;
        }

        float mean = 0.0;
        float SD = 0.0;

        //Printing Format:
        printf("_________________________________________________________________________________________________________________________________ \n");
        printf("--------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("Table No. %d\n", x + 1);
        printf("--------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("Description of ecperiment                                                                                                   Value\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("Population of the town (P)                                                                                             %10d\n", population);
        printf("Count of major service providers (S)                                                                                   %10d\n", (int)(serviceProvider * population));
        printf("Count of known infected persons (IR)                                                                                   %10d\n", infected);
        printf("--------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("Result                                                                                      Count of person who need to be tested\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------- \n");
        fprintf(fp,"_________________________________________________________________________________________________________________________________ \n");
        fprintf(fp,"--------------------------------------------------------------------------------------------------------------------------------- \n");
        fprintf(fp,"Table No. %d\n", x + 1);
        fprintf(fp,"--------------------------------------------------------------------------------------------------------------------------------- \n");
        fprintf(fp,"Description of ecperiment                                                                                                   Value\n");
        fprintf(fp,"--------------------------------------------------------------------------------------------------------------------------------- \n");
        fprintf(fp,"Population of the town (P)                                                                                             %10d\n", population);
        fprintf(fp,"Count of major service providers (S)                                                                                   %10d\n", (int)(serviceProvider * population));
        fprintf(fp,"Count of known infected persons (IR)                                                                                   %10d\n", infected);
        fprintf(fp,"--------------------------------------------------------------------------------------------------------------------------------- \n");
        fprintf(fp,"Result                                                                                      Count of person who need to be tested\n");
        fprintf(fp,"--------------------------------------------------------------------------------------------------------------------------------- \n");
        for (repeats = 0; repeats < 10; repeats++)
        {
            //printf("1\n");
            results[repeats] = doExperiment(population, serviceProvider, spinteraction, infected, normal_interactions100, 1);
        }
        calculate_M_SD(results, &mean, &SD);
        printf("Without any social distancing (T100)                                                       Mean: %0.001f & Standard Deviation: %0.001f\n", mean, SD);
        fprintf(fp, "Without any social distancing (T100)                                                       Mean: %0.001f & Standard Deviation: %0.001f\n", mean, SD);

        normal_interactions50 = (int)normal_interactions100 / 2;
        for (repeats = 0; repeats < 10; repeats++)
        {
            //printf("1\n");
            results[repeats] = doExperiment(population, serviceProvider, spinteraction, infected, normal_interactions50, 1);
        }
        calculate_M_SD(results, &mean, &SD);
        printf("With social distancing reducing contacts to 50%% (T50)                                      Mean: %0.001f & Standard Deviation: %0.001f\n", mean, SD);
        fprintf(fp, "With social distancing reducing contacts to 50%% (T50)                                      Mean: %0.001f & Standard Deviation: %0.001f\n", mean, SD);


        normal_interactions33 = (int)normal_interactions100 / 3;
        for (repeats = 0; repeats < 10; repeats++)
        {
            results[repeats] = doExperiment(population, serviceProvider, spinteraction, infected, normal_interactions33, 1);
        }
        calculate_M_SD(results, &mean, &SD);
        printf("With social distancing reducing contacts to 33%% (T33)                                     Mean:%7.001f & Standard Deviation: %0.001f\n", mean, SD);
        fprintf(fp,"With social distancing reducing contacts to 33%% (T33)                                     Mean:%7.001f & Standard Deviation: %0.001f\n", mean, SD);

        for (repeats = 0; repeats < 10; repeats++)
        {
            results[repeats] = doExperiment(population, serviceProvider, (spinteraction), infected, (int)(normal_interactions100 / 2), 0);
        } 
        calculate_M_SD(results, &mean, &SD);
        printf("With social distancing reducing contacts to 50%% with assigned service provider (TC)        Mean: %0.001f & Standard Deviation: %0.001f\n", mean, SD);
        fprintf(fp,"With social distancing reducing contacts to 50%% with assigned service provider (TC)        Mean: %0.001f & Standard Deviation: %0.001f\n", mean, SD);

        printf("--------------------------------------------------------------------------------------------------------------------------------- \n");
        printf("_________________________________________________________________________________________________________________________________ \n");
        printf("\n\n");

        fprintf(fp,"--------------------------------------------------------------------------------------------------------------------------------- \n");
        fprintf(fp,"_________________________________________________________________________________________________________________________________ \n");
        fprintf(fp,"\n\n");
    }

    /* population = 2000;
    infected = 5;
    serviceProvider = 0.03;
    spinteraction = 0.05;
    normal_interactions100 = 20;
    int row_count=0;
    doExperiment(population, serviceProvider, spinteraction, infected, normal_interactions100, 1);
    for(int i=0;i<population;i++)
    {
        row_count=0;
        for(int j=0;j<population;j++)
        {
            if(town[i][j]==1)
                row_count++;
        }
        printf("Row %d: %d\n", i+1, row_count);
    } */

    
    printf("************************************************************************************************************************************ \n");
    fprintf(fp,"************************************************************************************************************************************ \n");
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("TIME TAKEN: %f seconds. \n", time_taken);
    fprintf(fp,"TIME TAKEN: %f seconds. \n", time_taken);
    fclose(fp);
    return 0;
}