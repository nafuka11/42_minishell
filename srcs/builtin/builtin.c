/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:58:17 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/03 17:45:04 by nfukada          ###   ########.fr       */
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

int		exec_exit(char **args)
{
	(void)args;
	exit(1);
	return (EXIT_SUCCESS);
}

int		exec_cd(char **args)
{
	(void)args;
	ft_putstr_fd("cd called!\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int		exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (exec_exit(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (exec_cd(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (exec_echo(args));
	return (EXIT_FAILURE);
}

int		is_builtin(char **args)
{
	const char	*commands[] = {
		"exit", "cd", "echo", NULL
	};
	int			i;

	i = 0;
	if (args[0] == NULL)
		return (0);
	while (commands[i])
	{
		if (ft_strcmp(args[0], (char *)commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
