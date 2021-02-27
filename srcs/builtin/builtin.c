/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:58:17 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/27 11:28:14 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

/*
** Cause the shell to exit with a status of n.  If  n  is  omitted,
** the exit status is that of the last command executed.  A trap on
** EXIT is executed before the shell terminates.
**
** bash-3.2$ exit aaa
** exit
** bash: exit: aaa: numeric argument required
*/

void	exec_exit(char **args)
{
	(void)args;
	exit(1);
}

void	exec_cd(char **args)
{
	(void)args;
	ft_putstr_fd("cd called!\n", STDOUT_FILENO);
}

void	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		exec_exit(args);
	if (ft_strcmp(args[0], "cd") == 0)
		exec_cd(args);
	if (ft_strcmp(args[0], "echo") == 0)
		exec_echo(args);
}

int		is_builtin(char **args)
{
	const char	*commands[] = {
		"exit", "cd", "echo", NULL
	};
	int			i;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp(args[0], (char *)commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
