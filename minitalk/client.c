#include "minitalk.h"


// this following code is for the client
// our clients role is to send signals using the kill () syscall to our server 

void msg(int signal, siginfo_t *info, void *content)
{
	printf("MeSSage RecieVed !!\n");
}

void	send_len(int pid, int len, struct sigaction *sa)
{
	int loop;

	loop = (sizeof(int) * 8) - 1; // we took the number of bits in a int -1 to not over shift the last bit on the left
	while (loop >= 0)
	{
		send_bit(pid, (len >> loop) & 1);// we shift and countdown the number of bits left
		signal(30, msg);
		loop--;
	}
}

int main(int ac, char **av) // our client takes two params The server's PID and The string to send
{
	int		pid;
	struct sigaction client_action;

	if (ac != 3)
	{
		printf("invalid Arguments !!\n");
	}
		else if (kill(ft_atoi(av[1]), 0) < 0)
	{
		printf("ErrOr - PID is invalid!! \n");
		return (EXIT_FAILURE);
	}
	sigemptyset(&client_action.sa_mask);
	client_action.sa_sigaction = msg;
	client_action.sa_flags = SA_SIGINFO | SA_RESTART;
	pid = ft_atoi(av[1]);
	send_len(pid, ft_strlen(av[2]), &client_action);
	return (0);
}

// ./client pid message


// Check if pid is valid but sending a 0 sig to the pid (this won’t interrupt the servers normal flow of work).
// Call the function that will send the message’s length to the server.
// This function will get as parameters the pid of the server and the length of the message.
// 	in order to send we the (int) we will be shifting to the right starting with the biggest number, in order to do so we will need the number of bits that we will be sending. We get this number by using he next equation :
// 			number_of_shifts = sizeof(type_of_data) * 8 - 1;
// 			* type of data represents either :
// 				-> char
// 				-> int
// 			* 8 represents the number of bits in one byte;
// 			* -1 to not over shit
// Form the client we will be having these variables :
// 	-> server’s pid.
// 	-> message length
// 	-> message
// 	-> number of bits
// 	-> length was sent checker
// So I will try to go with a struct with the things I mentioned above first.
// Then try to create a ping pong signal between client and server and develop it from there.