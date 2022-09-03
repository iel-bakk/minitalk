# ifndef MINITALK_H
#define MINITALK_H

//libraries we are using 

#include <signal.h> // this the library we use when we want to call signal () and kill () syscalls
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // this is only for testing

// functions i'm using

int	ft_atoi(const char *str); // used to convert the pid form ascci to int
int	ft_strlen(char *str);  // used to get the lenght of the message we're sending
void	send_bit(int pid, int bit); // sends a sigusr1 or sigusr2 to the pid depending on the bit to send

#endif