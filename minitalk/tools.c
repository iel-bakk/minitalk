#include "minitalk.h"


int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str)
		len++;
	return (len);
}


int	ft_atoi(const char *str)
{
	int				sign;
	unsigned int	result;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return ((int)result * sign);
}

void	send_bit(int pid, int bit)
{
	printf("bit is %d\n", bit);
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
}

