/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minitalk_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/04 07:24:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/20 13:51:14 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "minitalk.h"

struct sigaction	create_sigaction_struct(int signum, \
void (*handler)(int, siginfo_t *, void *), int flag)
{
	struct sigaction	strct;

	sigemptyset(&strct.sa_mask);
	sigaddset(&strct.sa_mask, signum);
	strct.sa_sigaction = handler;
	strct.sa_flags = flag;
	return (strct);
}

void	error_checking(int argc, char *argv)
{
	int	i;

	i = 0;
	if (argc < 3)
		ft_exit_with_error("Please enter both a PID and a string\n", 1);
	else if (argc > 3)
		ft_exit_with_error("Please enter only a PID and a string\n", 1);
	if (ft_atoi(argv) == -1 || ((*argv == '0') && (*(argv + 1) == '\0')))
		ft_exit_with_error("Please enter the PID of the server\n", 1);
	if (*argv == '0')
		ft_exit_with_error("Please enter a valid PID number\n", 1);
	while (*(argv + i) != '\0')
	{
		if (*(argv + i) < '0' || *(argv + i) > '9')
			ft_exit_with_error("Please enter a valid PID number\n", 1);
		i++;
	}
}

void	wait_for_other_client(void)
{
	static int	j;

	if (j == 6)
		ft_exit_with_error("\nResponse time too long. \
		Either the server is being overwhelmed with requests \
		or the PID given is of a different process.\n", 1);
	j++;
	ft_printf("\nServer not responding. \
	Trying again in 10 seconds. Please be patient...\n");
	sleep(10);
}

void	clear_struct(t_message *current_message)
{
	free(current_message->str);
	current_message->str = NULL;
	current_message->length_received = 0;
	current_message->length = 0;
	current_message->current_str_position = 0;
}
