/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 13:22:02 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/08/09 18:06:48 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <unistd.h>
#include "minitalk.h"
#include "global_client.h"

void	handler_sigusr1(int signum, siginfo_t *info, void *context)
{
	g_flag = 2;
	(void)signum;
	(void)info;
	(void)context;
}

void	handler_sigusr2(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	g_flag = 1;
}

void	setup_signal_catchers_client(void)
{
	struct sigaction	first;
	struct sigaction	second;

	first = create_sigaction_struct(SIGUSR2, handler_sigusr1, SA_NODEFER);
	second = create_sigaction_struct(SIGUSR1, handler_sigusr2, SA_NODEFER);
	sigaction(SIGUSR1, &first, NULL);
	sigaction(SIGUSR2, &second, NULL);
}

int	main(int argc, char *argv[])
{
	int	pid;

	error_checking(argc, argv[1]);
	pid = ft_atoi(argv[1]);
	setup_signal_catchers_client();
	send_pid(pid);
	send_str_len(pid, argv[2]);
	send_str(pid, argv[2]);
	return (1);
}
