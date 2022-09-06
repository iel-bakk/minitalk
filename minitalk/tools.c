#include "minitalk.h"


void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

void	configure_sigaction_signals(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
	{
		write(1, "error - could not setup SIGUSR1\n", 31);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, sa, NULL) < 0)
	{
		write(1, "error - could not setup SIGUSR2\n", 31);
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
{
	unsigned int	result;

	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return ((int)result);
}

void	send_bit(int pid, int bit, int to_pause)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) != 0)
		{
			printf("ErrOr when sending a bit!!");
			exit(EXIT_FAILURE);
		}
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) != 0)
		{
			printf("ErrOr when sending a bit!!");
			exit(EXIT_FAILURE);
		}
	}
	if (to_pause != 0)
		pause();
}

void	initialise_info(t_client_model	*data)
{
	if (data->dont_initialize != 1)
	{
		data->server_pid = 0;
		data->msg_lenght = 0;
		data->message = NULL;
		data->shifts = 0;
		data->data = 0;
		data->fs_check = 0;
		data->dont_initialize = 1;
	}
}

void	reset_struct(t_client_model *data)
{
	free(data->message);
	data->dont_initialize = 2;
	initialise_info(data);
	write(1, "MEMORY IS FREEEEEE!!!\n", 22);
}