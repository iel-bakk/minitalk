#include "minitalk.h"


// this following code is for the client
// our clients role is to send signals using the kill () syscall to our server 

void msg(int signal, siginfo_t *info, void *content)
{
	if (signal == SIGUSR1)
	{
		ft_putstr("sending... sucsess!!\n");
	}
	else if (signal == SIGUSR2)
	{
		ft_putstr("Message Sent!!\n");
		exit(EXIT_SUCCESS);
	}
}

void	send_char(int pid, char c)
{
	int		shift;
	char	bit;

	shift = (sizeof(char) * 8) - 1;
	while (shift >= 0)
	{
		bit = (c >> shift) & 1;
		send_bit(pid, bit, 1);
		shift--;
	}
}

void	send_lenght(int	pid, int num)
{
	int		shift;
	char	bit;

	shift = (sizeof(int) * 8) - 1;
	while (shift >= 0)
	{
		bit = (num >> shift) & 1;
		send_bit(pid, bit, 1);
		shift--;
	}
}

void	send_msg(t_client_model *data)
{
	int	i;

	i = 0;
	send_lenght(data->server_pid, data->msg_lenght);
	while (data->message[i] != '\0')
		send_char(data->server_pid, data->message[i++]);
	send_char(data->server_pid, '\0');
}

int main(int ac, char **av) // our client takes two params The server's PID and The string to send
{
	struct sigaction	client_action;
	t_client_model		msg_info;

	if (ac != 3)
	{
		printf("invalid Arguments !!\n");
		return (EXIT_FAILURE);
	}
	else if (kill(ft_atoi(av[1]), 0) < 0)
	{
		printf("ErrOr - PID is invalid!! \n");
		return (EXIT_FAILURE);
	}
		initialise_info(&msg_info);
		sigemptyset(&client_action.sa_mask);
		client_action.sa_sigaction = msg;
		client_action.sa_flags = SA_RESTART;
		msg_info.server_pid = ft_atoi(av[1]);
		msg_info.msg_lenght = ft_strlen(av[2]);
		msg_info.message = av[2];
		configure_sigaction_signals(&client_action);
		send_msg(&msg_info);
	return (0);
}

// ./client pid message


// Check if the server pid is valid buy sending a 0 sig to the pid (this won’t interrupt the servers normal flow of work).
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