#include "minitalk.h"


// this following code is for the server
// our server recieves signals from our client and fonctions depending on th recieved signal

void	lenght_recieved_check(t_client_model *data)
{
	if (data->shifts == (sizeof(int) * 8) && data->fs_check == 0)
	{
		data->msg_lenght = data->data;
		data->data = 0;
		data->fs_check = 1;
		printf("%d len\n", data->msg_lenght);
		data->message = (char *)malloc(sizeof(char) * data->msg_lenght + 1);
		if (!data->message)
		{
			ft_putstr("Allocation ErOOr!!\n");
			exit(EXIT_FAILURE);
		}
		data->message[data->msg_lenght] = '\0';
		write(1, "MeSSaGe LengTH ReCieVeD!!\n", 26);
		data->shifts = 0;
	}
}

void	is_message_recived(t_client_model *data, int *i)
{
	int pid;

	if (data->shifts == 8 && data->fs_check == 1)
	{
		data->message[*i] = data->data;
		(*i)++;
		if (data->data == '\0')
		{
			pid = data->server_pid;
			write(1, "MessAge RecieVed : ", 19);
			ft_putstr(data->message);
			write(1, "\n", 1);
			reset_struct(data);
			send_bit(pid, SIGUSR2, 0);
		}
		data->data = 0;
		data->shifts = 0;
	}
}

void	server_handler(int sig, siginfo_t *info, void* secret)
{
	static t_client_model	data;
	static int				i; // static int is by default 0

	usleep(180);
	(void)secret;
	(void)info;
	if (sig == SIGUSR2 && data.fs_check == 0)
		data.data |= 1 << (((sizeof(int) * 8 - 1)) - data.shifts);
	else if (sig == SIGUSR2 && data.fs_check == 1)
		data.data |= 1 << (((sizeof(char) * 8 - 1)) - data.shifts);
	data.shifts++;
	ft_putstr("Bit ReciEved :)\n");
	lenght_recieved_check(&data);
	is_message_recived(&data, &i);
	send_bit(info->si_pid, 0, 0);
}

// typedef struct {
// 	int si_signo;
// 	int si_code;
// 	union sigval si_value;
// 	int si_errno;
// 	pid_t si_pid;
// 	uid_t si_uid;
// 	void *si_addr;
// 	int si_status;
// 	int si_band;
// } siginfo_t;

// Fields of the Structure

// The siginfo_t structure contains the following fields:

// si_signo  

//     Signal number being delivered. This field is always set.
// si_code  

//     Signal code. This field is always set. Refer to Signal Codes for information on valid settings, and for which of the remaining fields are valid for each code.
// si_value  

//     Signal value.
// si_errno  

//     If non-zero, an errno value associated with this signal.
// si_pid  

//     Process ID of sending process.
// si_uid  

//     Real user ID of sending process.
// si_addr  

//     Address at which fault occurred.
// si_status  

//     Exit value or signal for process termination.
// si_band  

//     Band event for SIGPOLL/SIGIO.
// st_mtime  

//     Time of last data modification.


int main(void)
{

	struct sigaction	s_server;

	sigemptyset(&s_server.sa_mask);
	s_server.sa_sigaction = server_handler;
	s_server.sa_flags = SA_SIGINFO | SA_RESTART;
	configure_sigaction_signals(&s_server);
	printf("%d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}