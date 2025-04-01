#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <syscall.h>

int sigint_receiver = 0;

void	sigaction_init(struct sigaction * sa, void (*handler) (int, siginfo_t *, void *))
{
	memset(sa, 0, sizeof(struct sigaction));
	sa->sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
}

void	handler(int signature, siginfo_t * a, void * b)
{
	char buf[16];
	sprintf(buf, "%d", signature);
	puts(buf);
	if (signature == SIGINT)
		sigint_receiver = 1;
	system("ps -f");
	sleep(1);
}

void	close_active_process(int pid)
{
	sigint_receiver = 0;
	kill(pid, SIGINT);
}

void	loop(int pid_fork)
{
	char * line;
	
	while ((line = readline("minishell>")))
	{
		sleep(1);
		printf("%d\n", getpid());
		if (sigint_receiver)
			close_active_process(pid_fork);
		system("ps -f");
	}
}

int		main()
{
	int	pid;
	struct sigaction sa;

	sigaction_init(&sa, handler);
	sigaction(SIGINT, &sa, 0);
	pid = fork();
	printf("%d\n", pid);
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execve("dummy", NULL, NULL);
	else
	{
		system("ps -f");
		loop(pid);
	}
	exit(EXIT_SUCCESS);
}
