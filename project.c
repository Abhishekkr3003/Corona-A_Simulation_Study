#include "project.h"

int doExperiment(int population, double serviceProvider, double spinteraction, int infected, int normal_interactions, int indicator)
{
    for (int i = 0; i < population; i++)
    {
        meeting[i] = 0;
        infection[i] = 0;
        interaction[i] = 0;
        for (int j = 0; j < population; j++)
            town[i][j] = 0;
    }
    int spinteractions = (int)(spinteraction * (population-(serviceProvider*population)));
    //printf("spinteraction: %d\n",spinteractions);
    int i = 0, j = 0;
    int threshold, totalInfected = 0;
    //printf("1\n");
    threshold = serviceProvider * population;
    set_service(threshold, spinteractions, population, normal_interactions);
    set_initial_infected(infected, population);
    //printf("2\n");
    if (indicator)
        setup_town(spinteractions, population);
    else
        setup_town_2(spinteractions, population);
    //printf("3\n");

    int total = 0;
    for (i = 0; i < population; i++)
    {
        //printf("Interaction for %d is %d\n", i + 1, meeting[i]);
        total += meeting[i];
        /*for(j=0;j<population;j++)
        {
            if(town[i][j]==1)
                printf("P%d ",j+1);
        }
        printf("\n\n"); */
    }
    //printf("4\n");
    //printf("Effective Interactions:                                                                                            %d/%d\n", total, (int)(normal_interactions * (population - serviceProvider * population) + 2 * (int)(spinteraction * (population)) * serviceProvider * population));

    
    //printf("5\n");
    totalInfected = set_infected(population, infected);
    //printf("6\n");
    //printf("Total Infected                                                                                                               %d\n\n", totalInfected);
    //printf("FIND:*************************************\n");
    //transClosure(population);
    return totalInfected;
}

void transClosure(int population)
{
    for (int k = 0; k < population; k++)
        for (int i = 0; i < population; i++)
            for (int j = 0; j < population; j++)
                town[i][j] = town[i][j] || (town[i][k] && town[k][j]);
}

void set_initial_infected(int infected, int population)
{
    int count = 0, index = 0, i = 0;
    //printf("Initially Infected: ");
    while (count < infected)
    {
        if (randomYes())
        {
            assert(index != infected);
            infection[index++] = 1;
            //printf("C%d ", i+1);
            count++;
        }
        i = (i + 1) % population;
    }
    //printf("\n");
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

/* void infection_rec(int index, int population)
{

    if (infection[index] == 1)
        return;
    infection[index] = 1;
    for (int j = 0; j < population; j++)
    {
        if (town[index][j] == 1)
        {
            infection_rec(j, population);
        }
    }
    return;
} */

int set_infected(int population, int infected)
{
    /* for (int i = 0; i < population; i++)
        infection[i] = 0;

    for (int i = 0; i < infected; i++)
        infection_rec(initial_inf[i], population);

    int count = 0;
    for (int i = 0; i < population; i++)
    {
        if (infection[i] == 1)
            count++;
    }
    return count; */
    int count=0;
    for(int i=0;i<population;i++)
    {
        if(infection[i]==1)
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
    while (common--)
    {
        if (randomYes() == 1)
            return 1;
    }
    return 0;
}

void set_service(int threshold, int spinteraction, int population, int normal_interactions)
{
    //printf("Normal:%d", normal_interactions);
    int i = 0, count = 0, yesService = 0;
    int service_meeting = spinteraction;

    while (count < threshold)
    {
        yesService = randomYes();
        if (yesService == 1)
        {
            if (interaction[i] != service_meeting)
            {
                interaction[i] = spinteraction;
                count++;
            }
        }
        else if (interaction[i] != service_meeting)
            interaction[i] = normal_interactions;
        i = (i + 1) % population;
    }
    for (; i < population; i++)
    {
        if (interaction[i] != service_meeting)
            interaction[i] = normal_interactions;
    }
}

void setup_town(int spinteraction, int population)
{
    int i = 0, j = 0, yesMeeting = 0;

    for (i = 0; i < population; i++)
    {
        //if(interaction[i] == spinteraction)
        //continue;
        //printf("i=%d\n", i);
        //printf("Service %d %d\n", i+1, interaction[i]);
        j = i;

        while (j < population && meeting[i] < interaction[i])
        {
            if (interaction[j] == spinteraction) //A service provider won't meet any any other service provider
            {
                //j = (j + 1) % population;
                //j = (j == population - 1) ? i : j + 1;
                if (i < (population-0.1*population))
                    j = (j == population - 1) ? i : j + 1;
                else
                    j = (j + 1) % population;
                continue;
            }
            //printf("i=%d j=%d meet=%d\n", i, j, meeting[i]);
            yesMeeting = baisedYes(i, j);
            //printf("After Baised yes\n");
            if (yesMeeting == 1)
            {
                if(infection[i]==1 || infection[j]==1)
                {
                    infection[i]=infection[j]=1;
                }
                town[i][j] = 1;
                town[j][i] = 1;
                meeting[i]++;
                meeting[j]++;
            }
            /* else if (town[i][j] != 1)
            {
                town[i][j] = 0;
                town[j][i] = 0;
            } */
            //j++;
            //j = (j + 1) % population;
            if (i < (population-0.1*population))
                j = (j == population - 1) ? i : j + 1;
            else
                j = (j + 1) % population;
            //printf("i=%d  j= %d\n", i,j);
        }
    }
}

void setup_town_2(int spinteraction, int population)
{
    int i = 0, j = 0, yesMeeting = 0;

    for (i = 0; i < population; i++)
    {
        //printf("i=%d\n", i);
        //printf("Service %d %d\n", i+1, interaction[i]);
        j = i;
        if (interaction[i] != spinteraction)
        {
            while (j < population && meeting[i] < interaction[i])
            {
                //printf("In while\n");
                if (interaction[j] == spinteraction)
                {
                    //j = (j + 1) % population;
                    //j = (j == population - 1) ? i : j + 1;
                    if (i < (population-0.1*population))
                        j = (j == population - 1) ? i : j + 1;
                    else
                        j = (j + 1) % population;
                    continue;
                }

                //printf("i=%d j=%d meet=%d interaction=%d\n", i, j, meeting[i], interaction[i]);
                yesMeeting = baisedYes(i, j);
                //printf("After Baised yes\n");
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
                }
                // else
                // {
                //     meeting[i]++;
                //     meeting[j]++;
                // }

                // else if (town[i][j] != 1)
                // {
                //     //printf("NO\n");
                //     town[i][j] = 0;
                //     town[j][i] = 0;
                // }
                //j++;
                //j = (j + 1) % population;
                //j = (j == population - 1) ? i : j + 1;
                //printf("i=%d  j= %d\n", i,j);
                
                if (i < (population-0.1*population))
                    j = (j == population - 1) ? i : j + 1;
                else
                    j = (j + 1) % population;
            }
            
        }

        else
        {
            while (j < population && meeting[i] < interaction[i])
            {
                if (interaction[j] == spinteraction)
                {
                    //j = (j + 1) % population;
                    //j = (j == population - 1) ? i : j + 1;
                    if (i < (population-0.1*population))
                        j = (j == population - 1) ? i : j + 1;
                    else
                        j = (j + 1) % population;
                    continue;
                }
                if ((i % 2) != (j % 2))
                {
                    //j = (j + 1) % population;
                    //j = (j == population - 1) ? i : j + 1;
                    if (i < (population-0.1*population))
                        j = (j == population - 1) ? i : j + 1;
                    else
                        j = (j + 1) % population;
                    continue;
                }
                yesMeeting = baisedYes(i, j);
                //printf("After Baised yes\n");
                if (yesMeeting == 1)
                {
                    if (infection[i] == 1 || infection[j] == 1)
                    {
                        infection[i] = infection[j] = 1;
                    }
                    town[i][j] = 1;
                    town[j][i] = 1;
                    meeting[i]++;
                    meeting[j]++;
                }
                // else if (town[i][j] != 1)
                // {
                //     town[i][j] = 0;
                //     town[j][i] = 0;
                // }
                //j++;
                //j = (j + 1) % population;
                //j = (j == population - 1) ? i : j + 1;
                //printf("i=%d  j= %d\n", i,j);
                if (i < (population-0.1*population))
                    j = (j == population - 1) ? i : j + 1;
                else
                    j = (j + 1) % population;
            }
        }
    }
}
