/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sending_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 22:16:28 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/10/26 16:18:15 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int g_flag;

void	send_bit(int bit, int pid)
{
	int	check;

	if (bit == 1)
		check = kill(pid, SIGUSR1);
	else
		check = kill(pid, SIGUSR2);
	if (check == -1)
		ft_exit_with_error("Sending signal to server failed. \
		Please make sure you've entered the server PID\n", 1);
	usleep(1000000);
}

void	send_char(unsigned char c, int pid)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		g_flag = 0;
		send_bit(c & 1, pid);
		if (g_flag == 0)
			continue ;
		c = c >> 1;
		j++;
	}
}

void	send_str(int pid, char *str)
{
	int		i;

	i = 0;
	while (*(str + i) != '\0')
	{
		send_char(*(str + i), pid);
		i++;
	}
	send_char('\0', pid);
	if (g_flag == 1)
		ft_putstr_fd("Message received\n", 1);
}

void	send_str_len(int pid, char *str)
{
	size_t	length;
	int		i;

	length = ft_strlen(str);
	i = 0;
	while (i < 64)
	{
		send_bit(length & 1, pid);
		length = length >> 1;
		i++;
	}
	if (g_flag == 1)
		ft_exit_with_error("Malloc failure on server side. Shutting down.", 12);
}

void	send_pid(int pid)
{
	while (1)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_exit_with_error("Sending signal to server failed. \
			Please make sure you've entered the server PID\n", 1);
		if (sleep(3) == 0)
		{
			wait_for_other_client();
			continue ;
		}
		break ;
	}
}
