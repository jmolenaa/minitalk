/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 13:22:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/10/26 16:29:59 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minitalk.h"
#include "libft.h"

int	g_flag;

void	handle_sigusr1(int signum, siginfo_t *info, void *context)
{
	static int	current_pid;

	usleep(10);
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
	usleep(10);
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
		usleep(10);
	}
}

void	setup_signal_catchers_server(void)
{
	struct sigaction	first;
	struct sigaction	second;
	int					flags;

	flags = SA_SIGINFO | SA_NODEFER | SA_RESTART;
	first = create_sigaction_struct(SIGUSR2, handle_sigusr1, flags);
	second = create_sigaction_struct(SIGUSR1, handle_sigusr2, flags);
	sigaction(SIGUSR1, &first, NULL);
	sigaction(SIGUSR2, &second, NULL);
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	sleep(1);
	setup_signal_catchers_server();
	run_server();
	return (1);
}
