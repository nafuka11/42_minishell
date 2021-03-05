/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/05 16:20:53 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "utils.h"

static void		wait_commands(t_command *command)
{
	extern int	g_status;
	int			status;
	t_bool		has_child;
	t_bool		catch_sigint;
	int			signal;

	has_child = FALSE;
	catch_sigint = FALSE;
	while (command)
	{
		if (command->pid != NO_PID)
		{
			if (waitpid(command->pid, &status, 0) < 0)
				error_exit(NULL);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				catch_sigint = TRUE;
			has_child = TRUE;
		}
		command = command->next;
	}
	if (has_child == FALSE)
		return ;
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		g_status = signal + 128;
	}
	if (catch_sigint)
		ft_putendl_fd("", STDERR_FILENO);
}

static void		exec_pipeline(t_node *nodes)
{
	extern int		g_status;
	t_command		*command;
	int				pipe[2];
	t_pipe_state	pipe_state;

	pipe_state = PIPE_WRITE_ONLY;
	while (nodes->type == NODE_PIPE)
		nodes = nodes->left;
	command = nodes->command;
	while (command)
	{
		g_status = exec_command(command, &pipe_state, pipe);
		command = command->next;
	}
	wait_commands(nodes->command);
}

static void		exec_list(t_node *nodes)
{
	extern int		g_status;
	t_pipe_state	pipe_state;

	pipe_state = NO_PIPE;
	if (!nodes)
	{
		return ;
	}
	if (nodes->type == NODE_PIPE)
	{
		exec_pipeline(nodes);
	}
	else
	{
		g_status = exec_command(nodes->command, &pipe_state, NULL);
		wait_commands(nodes->command);
	}
}

void			exec_nodes(t_node *nodes)
{
	if (!nodes)
	{
		return ;
	}
	if (nodes->type == NODE_SEMICOLON)
	{
		exec_nodes(nodes->left);
		exec_nodes(nodes->right);
	}
	else
	{
		exec_list(nodes);
	}
}
