/*
	This file has the definition of all the functions defined in project.h
*/

#include "project.h"

int doExperiment(int population, double serviceProvider, double spinteraction, int infected, int normal_interactions, int indicator)
{
    for (int i = 0; i < population; i++)
    {
        meeting[i] = 0;
        infection[i] = 0;
        isServiceMan[i] = 0;
        for (int j = 0; j < population; j++)
            town[i][j] = 0;
    }
    int spinteractions = (int)(spinteraction * (population ));
    int i = 0, j = 0;
    int threshold, totalInfected = 0;
    threshold = serviceProvider * population;
    set_service(threshold, population);
    set_initial_infected(infected, population);
    int interactions_people_do = normal_interactions * (population - threshold);
    if (indicator)
        setup_town(spinteractions * threshold*2, population, interactions_people_do);
    else
        setup_town_2(spinteractions * threshold*2, population, interactions_people_do);
    totalInfected = count_infected(population, infected);
    return totalInfected;
}

void set_initial_infected(int infected, int population)
{
    int count = 0, index = 0, i = 0;
    while (count < infected)
    {
        if (randomYes())
        {
            assert(index != infected);
            infection[index++] = 1;
            count++;
        }
        i = (i + 1) % population;
    }
}

void calculate_M_SD(int results[], float *mean, float *SD)
{
    float sum = 0.0, var = 0.0;
    int i;
    for (i = 0; i < 10; i++)
    {
        sum += results[i];
    }
    *mean = sum / 10;
    for (i = 0; i < 10; ++i)
        var += pow(results[i] - *mean, 2);
    *SD = sqrt(var / 10);
}

int count_infected(int population, int infected)
{
    int count = 0;
    for (int i = 0; i < population; i++)
    {
        if (infection[i] == 1)
            count++;
    }
    return count;
}

int randomYes()
{
    int temp;
    temp = 1 + rand() % 1000;
    if (temp == 1000)
        return 1;
    else
        return 0;
}

int gcd(int a, int b)
{
    int i;
    if (b == 0)
    {
        return a;
    }
    else
    {
        i = a % b;
        return gcd(b, i);
    }
}
int isprime(int n)
{
    int i, flag = 1;
    for (i = 2; i <= (sqrt(n)); i++)
    {
        if (n % i == 0)
        {
            flag = 0;
            return 1;
        }
    }
    return 0;
}

int countPrimeFactors(int a, int b)
{
    if (isprime(a) || isprime(b))
        return 1;
    int c;
    int factors[1000];
    c = gcd(a, b);
    int i = 2, k = 0;
    while (c != 1)
    {
        if (c % i == 0)
        {
            while (c % i == 0)
            {
                c = c / i;
                factors[k] = i;
                k++;
            }
        }
        i++;
    }
    return k;
}

int baisedYes(int x, int y)
{
    int common = countPrimeFactors(x + 1001, y + 1001);
    //Return biased interaction
    if (rand()%1000 <=common)
            return 1;
    return 0;
}

void set_service(int threshold, int population)
{
    int i = 0, count = 0, yesService = 0;
    while (count < threshold)
    {
        yesService = randomYes();
        if (yesService == 1)
        {
            if (isServiceMan[i] != 1)
            {
                isServiceMan[i] = 1;
                count++;
            }
        }
        else if (isServiceMan[i] != 1)
            isServiceMan[i] = 0;
        i = (i + 1) % population;
    }
    for (; i < population; i++)
    {
        if (isServiceMan[i] != 1)
            isServiceMan[i] = 0;
    }
}

void setup_town(int spinteraction, int population, int interactions_people_do)
{
    int i = 0, j = 0, yesMeeting = 0, countInteractions = 0, count_service_interaction = 0, people_done = 0, sp_done = 0;

    for (i = 0; countInteractions + count_service_interaction < interactions_people_do + spinteraction; i = (i == population - 1) ? 0 : i + 1)
    {
        if (isServiceMan[i] == 0)
        {
            if (!people_done)
            {
                j = i;

                while (j < population)
                {
                    if (isServiceMan[j] == 1) //A service provider won't meet any any other service provider
                    {
                        j++;
                        continue;
                    }
                    yesMeeting = baisedYes(i, j);
                    if (yesMeeting == 1)
                    {
                        if(infection[i]==1 || infection[j]==1)
                        {
                            infection[i] = infection[j] = 1;
                        }
                        town[i][j] = 1;
                        town[j][i] = 1;
                        meeting[i]++;
                        meeting[j]++;
                        countInteractions += 2;
                        if (countInteractions >= interactions_people_do)
                        {
                            people_done = 1;
                            break;
                        }
                    }
                    j++;
                }
            }
        }
        else
        {
            if (!sp_done)
            {
                j = i;

                while (j < population)
                {
                    if (isServiceMan[j] == 1) //A service provider won't meet any any other service provider
                    {
                        j++;
                        continue;
                    }
                    yesMeeting = baisedYes(i, j);
                    if (yesMeeting == 1 && town[i][j] != 1)
                    {
                        if(infection[i]==1 || infection[j]==1)
                        {
                            infection[i] = infection[j] = 1;
                        }
                        town[i][j] = 1;
                        town[j][i] = 1;
                        meeting[i]++;
                        meeting[j]++;
                        count_service_interaction += 2;
                        if (count_service_interaction >= spinteraction)
                        {
                            sp_done = 1;
                            break;
                        }
                    }
                    j++;
                }
            }
        }
    }
}

void setup_town_2(int spinteraction, int population, int interactions_people_do)
{
    int i = 0, j = 0, yesMeeting = 0, countInteractions = 0, count_service_interaction = 0, people_done = 0, sp_done = 0;

    for (i = 0; countInteractions + count_service_interaction < interactions_people_do + spinteraction; i = (i == population - 1) ? 0 : i + 1)
    {
        if (isServiceMan[i] == 0)
        {
            if (!people_done)
            {
                j = i;

                while (j < population)
                {
                    if (isServiceMan[j] == 1) //A service provider won't meet any any other service provider
                    {
                        j++;
                        continue;
                    }
                    yesMeeting = baisedYes(i, j);
                    if (yesMeeting == 1)
                    {
                        if(infection[i]==1 || infection[j]==1)
                        {
                            infection[i] = infection[j] = 1;
                        }
                        town[i][j] = 1;
                        town[j][i] = 1;
                        meeting[i]++;
                        meeting[j]++;
                        countInteractions += 2;
                        if (countInteractions >= interactions_people_do)
                        {
                            people_done = 1;
                            break;
                        }
                    }
                    j++;
                }
            }
        }
        else
        {
            if (!sp_done)
            {
                j = i;

                while (j < population)
                {
                    if (isServiceMan[j] == 1|| i&1!=j&1)  //A service provider won't meet any any other service provider
                    {
                        j++;
                        continue;
                    }
                    yesMeeting = baisedYes(i, j);
                    if (yesMeeting == 1 && town[i][j] != 1)
                    {
                        if(infection[i]==1 || infection[j]==1)
                        {
                            infection[i] = infection[j] = 1;
                        }
                        town[i][j] = 1;
                        town[j][i] = 1;
                        meeting[i]++;
                        meeting[j]++;
                        count_service_interaction += 2;
                        if (count_service_interaction >= spinteraction)
                        {
                            sp_done = 1;
                            break;
                        }
                    }
                    j++;
                }
            }
        }
    }
}

