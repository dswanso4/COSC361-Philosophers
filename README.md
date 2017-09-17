# COSC361-Philosophers
Simulates the dining philosophers problem

# philosophers.c
This file simulates the dining philosophers issue where there are 5 philosophers that each have 2 meals 
to eat and are sitting around a circular table. There is a chopstick set between each philosopher so 
that not all can eat at the same time. The philosopher takes some random time between 1 and 3 seconds 
to finish their meal and then sets down the chopstick. The program uses the Pthreads library to run 
the application on multiple threads. Thread communication is essential in this problem to avoid 
deadlocks.

./philosophers 

