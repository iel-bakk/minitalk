#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int a = 0;
void    fun(int sign, siginfo_t *siginfo, void *ptr)
{
    a = sign;
}

int main()
{
    // // Calculate the time taken by fun()
    // /*
    // clock_t t;
    // t = clock();
    // fun();
    // t = clock() - t;
    // double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    // printf("fun() took %f seconds to execute \n", time_taken);
    // */
    struct sigaction test;
    sigsetmask(test.sa_mask);
    sigaddset(&test.sa_mask, SIGUSR2);
    test.sa_sigaction = fun;
    sigaction(31, &test, NULL);
    printf ("hello there my name is : %d\n", getpid());
    printf("we are pausing\n");
    pause();
    printf("hello there \n");
    return 0;
}