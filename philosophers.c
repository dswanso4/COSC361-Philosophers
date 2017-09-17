#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

//Constants
#define Rand_Time (random() % 2000000 + 1000000) // 1s < Rand_Time < 3s
#define NumPhilosophers 5
#define NumMeals 2
#define VERBOSE true

//Function prototypes
void *philosopher(int n);
int Right_Chopstick(int id);
int Left_Chopstick(int id);
void GetLeftChopstick(int id);
void GetRightChopstick(int id);
void Replace_Chopsticks(int n, int mealsEaten);
void Take_Chopsticks(int n);

//Fork struct definition
typedef struct fork
{
    pthread_mutex_t lock;
} frk;

//Initialization statment of the structs and forks
pthread_t p[NumPhilosophers];
frk f[NumPhilosophers];

//Main function that sets up the structs and threads, and operates on the mutexes.

int main ( void )
{
    int i;

    //Sets up fork structs
    for (i = 0; i < NumPhilosophers; ++i)
    {
        pthread_mutex_init(&f[i].lock, NULL);
    }

    //Create threads, join threads, and then destroy mutexes before quitting
    for (i = 0; i < NumPhilosophers; ++i)
    {
        pthread_create(&p[i], NULL, (void *)philosopher, (int *)i);
    }
    for (i = 0; i < NumPhilosophers; ++i)
    {
        pthread_join(p[i], NULL);
    }
    for (i = 0; i < NumPhilosophers; ++i)
    {
        pthread_mutex_destroy(&f[i].lock);
    }

    return 0;
}

//Function that represents the actions of a philospher.

void *philosopher(int n)
{
    int mealsEaten;

    // Philosopher eats until it is finished with NumMeals
    for (mealsEaten = 0; mealsEaten < NumMeals; ++mealsEaten)
    {
        //Thinking...
        usleep(Rand_Time);

        Take_Chopsticks(n);

        if (VERBOSE)printf("\nPhilosopher %d is eating meal %d.", n, mealsEaten);
        //Eating...
        usleep(Rand_Time);

        //Put chopsticks down
        Replace_Chopsticks(n, mealsEaten);
    }

    //Finish up and leave
    if (VERBOSE)printf("\nPhilosopher %d is done and is leaving.", n);
    if (VERBOSE)printf("\n");
}

//Function that determines which chopstick to grab first and then grabs them by calling seperate functions in different orders.

void Take_Chopsticks(int n)
{
    //Check for the lower numbered chopstick and grab it first
    if (Left_Chopstick(n) > Right_Chopstick(n))
    {
        GetLeftChopstick(n);
        GetRightChopstick(n);
    }
    else
    {
        GetRightChopstick(n);
        GetLeftChopstick(n);
    }
}

// Function that grabs the left chopstick

void GetLeftChopstick(int n)
{
    if (VERBOSE)printf("\nPhilosopher %d is attempting to grab the left chopstick.", n);
    pthread_mutex_lock(&f[Left_Chopstick(n)].lock);
    if (VERBOSE)printf("\nPhilosopher %d has grabbed the left chopstick.", n);
}

// Function that grabs the right chopstick

void GetRightChopstick(int n)
{
    if (VERBOSE)printf("\nPhilosopher %d is attempting to grab the right chopstick.", n);
    pthread_mutex_lock(&f[Right_Chopstick(n)].lock);
    if (VERBOSE)printf("\nPhilosopher %d has grabbed the right chopstick.", n);
}

// Function that returns the chopstick

void Replace_Chopsticks(int n, int mealsEaten)
{
    pthread_mutex_unlock(&f[Left_Chopstick(n)].lock);
    pthread_mutex_unlock(&f[Right_Chopstick(n)].lock);
    if (VERBOSE)printf("\nPhilosopher %d is finished eating meal %d.", n, mealsEaten);
}

//Returns the left chopstick id for philosopher #id

int Left_Chopstick(int id)
{
    return id;
}

//Returns the right chopstick id for philosopher #id

int Right_Chopstick(int id)
{
    return (id + 1) % NumPhilosophers;
}
