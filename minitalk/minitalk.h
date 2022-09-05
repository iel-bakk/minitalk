# ifndef MINITALK_H
#define MINITALK_H

//libraries we are using 

#include <signal.h> // this the library we use when we want to call signal () and kill () syscalls
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // this is only for testing

// defining structers

typedef struct s_client_model{
    int     server_pid;
    int     msg_lenght;
    int     data;
    char    *message; // message sent
    int     shifts; // number of shifts
    int     fs_check; // first step check
    int     dont_initialize;
} t_client_model;

// functions i'm using

int	    ft_atoi(const char *str); // used to convert the pid form ascci to int
int	    ft_strlen(char *str);  // used to get the lenght of the message we're sending
void	send_bit(int pid, int bit, int to_pause); // sends a sigusr1 or sigusr2 to the pid depending on the bit to send <> the pause variale is used to pause from client side only 
void	configure_sigaction_signals(struct sigaction *sa);
void	initialise_info(t_client_model	*setup);
void    ft_putstr(char *str);
void	reset_struct(t_client_model *data);
#endif