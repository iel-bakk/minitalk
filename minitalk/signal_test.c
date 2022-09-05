#include "minitalk.h"

void    handler(int sign)
{
    printf("the signal is %d\n", sign);
}

int main(int ac, char **av)
{
    int pid;
    int i = 0;

    pid = ft_atoi(av[1]);
    signal(SIGUSR1, handler);
    while (1)
    {
        kill(pid, SIGUSR2);
        printf("my pid is %d\n", getpid());
        pause();
        i++;
    }
    return (0);
}