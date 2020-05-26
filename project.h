#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#define POPULATION 10000
#define INFECTED 100

int town[POPULATION][POPULATION];
int meeting[POPULATION];
int interaction[POPULATION];
int initial_inf[INFECTED];
int infection[POPULATION];

int random_no();
int randomYes();
int gcd(int a, int b);
int countPrimeFactors(int a, int b);
int baisedYes(int x, int y);
void set_service(int threshold, int spinteraction, int population, int normal_interactions);
void setup_town(int spinteraction, int population);
void setup_town_2(int spinteraction, int population);
int isprime(int n);
void set_initial_infected(int, int);
int set_infected(int, int);
void infection_rec(int index, int population);
int doExperiment(int, double, double, int, int normal_interactions, int indicator);
void calculate_M_SD(int results[], float *mean, float *SD);
void transClosure(int population);