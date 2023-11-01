/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   receiving_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 23:22:42 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/11/01 06:55:25 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

extern int g_flag;

size_t	receive_length(int flag, t_message *current_message)
{
	static size_t	length;
	static int		i;

	if (flag == 1)
		length = length + (__SIZE_MAX__ / 2 + 1);
	i++;
	if (i == 64)
	{
		current_message->length = length;
		current_message->length_received = 1;
		i = 0;
		length = 0;
		return (1);
	}
	length = length >> 1;
	return (0);
}

int	receive_char(int flag, t_message *current_message)
{
	static int				i;
	static unsigned char	c;

	if (flag == 1)
		c = c + (UCHAR_MAX / 2 + 1);
	i++;
	if (i == 8)
	{
		i = 0;
		*(current_message->str + current_message->current_str_position) = c;
		if (c == '\0')
			return (1);
		current_message->current_str_position++;
		c = 0;
	}
	c = c >> 1;
	return (0);
}

void	recieve_bit(int flag, t_message *current_message)
{
	if (current_message->length_received == 0)
	{
		if (receive_length(flag, current_message))
		{
			current_message->str = ft_calloc(current_message->length + 1, 1);
			if (current_message->str == NULL)
			{
				kill(current_message->pid, SIGUSR2);
				ft_exit_with_error("Malloc failure. Shutting down.\n", 12);
			}
		}
	}
	else
	{
		if (receive_char(flag, current_message))
		{
			write(1, current_message->str, current_message->length);
			write(1, "\n", 1);
			clear_struct(current_message);
			g_flag = 0;
			return ;
		}
	}
	g_flag = -1;
}

void	handle_signal(int flag)
{
	static t_message	current_message;
	int					check;

	if (flag > 2)
	{
		current_message.pid = flag;
		g_flag = -1;
		usleep(1000);
	}
	else
		recieve_bit(flag, &current_message);
	if (g_flag == 0)
		check = kill(current_message.pid, SIGUSR2);
	else
		check = kill(current_message.pid, SIGUSR1);
	if (check == -1)
	{
		clear_struct(&current_message);
		ft_exit_with_error("Sending signal to client failed. \
		Please exit client manually.\n", 1);
	}
}
