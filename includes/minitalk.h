/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/04 07:25:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/02/21 07:33:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>

typedef struct s_message
{
	size_t	length;
	char	*str;
	int		length_received;
	int		pid;
	size_t	current_str_position;
}			t_message;

struct sigaction	create_sigaction_struct(int signum, \
void (*handler)(int, siginfo_t *, void *), int flag);
void				send_pid(int pid);
void				send_str(int pid, char *str);
void				send_str_len(int pid, char *str);
void				wait_for_other_client(void);
void				error_checking(int argc, char *argv);
void				clear_struct(t_message *current_message);
void				handle_signal(int flag);

#endif