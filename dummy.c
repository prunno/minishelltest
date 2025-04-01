#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void	handler(int signature, siginfo_t * a, void * b)
{
	if (signature == SIGINT)
		puts("KILLED! :(");
	kill(getpid(), SIGKILL);
}

void
sigaction_init(struct sigaction * sa, void (*handler) (int, siginfo_t *, void *))
{
	memset(sa, 0, sizeof(struct sigaction));
	sa->sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
}

int	main(void)
{
	struct sigaction sa;

	sigaction_init(&sa, handler);
	sigaction(SIGINT, &sa, 0);
	while (1)
		usleep(10);
	return 0;
}
