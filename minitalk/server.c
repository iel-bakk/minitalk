#include "minitalk.h"


// this following code is for the server
// our server recieves signals from our client and fonctions depending on th recieved signal

void	configure_sigaction_signals(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) < 0)
	{
		printf("ErOOr could not setup SIGUSR1");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, sa, NULL) < 0)
	{
		printf("ErOOr could not setup SIGUSR2");
		exit(EXIT_FAILURE);
	}
}

void	server_handler(int sig, siginfo_t *info, void* secret)
{
	(void)secret;
	(void)info;
	printf("signal is %d\n", sig);
	printf("client's pid is %d\n", info->si_pid);
	kill(info->si_pid, 30);
	pause();
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