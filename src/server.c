/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 13:22:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/02/21 07:41:37 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minitalk.h"
#include "libft.h"
#include "global_server.h"

void	handle_sigusr1(int signum, siginfo_t *info, void *context)
{
	static int	current_pid;

	usleep(100);
	(void)context;
	(void)signum;
	if (g_flag == 0)
	{
		current_pid = info->si_pid;
		g_flag = info->si_pid;
	}
	else if (info->si_pid == current_pid)
		g_flag = 1;
}

void	handle_sigusr2(int signum, siginfo_t *info, void *context)
{
	usleep(100);
	(void)context;
	(void)info;
	(void)signum;
	g_flag = 2;
}

void	run_server(void)
{
	while (1)
	{
		if (g_flag > 0)
			handle_signal(g_flag);
		usleep(100);
	}
}

void	setup_signal_catchers_server(void)
{
	struct sigaction	first;
	struct sigaction	second;
	int					flags;

	flags = SA_SIGINFO | SA_RESTART;
	first = create_sigaction_struct(SIGUSR2, handle_sigusr1, flags);
	second = create_sigaction_struct(SIGUSR1, handle_sigusr2, flags);
	sigaction(SIGUSR1, &first, NULL);
	sigaction(SIGUSR2, &second, NULL);
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	setup_signal_catchers_server();
	run_server();
	return (1);
}
