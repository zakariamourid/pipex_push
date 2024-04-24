/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:14:19 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/24 18:14:21 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(char *cmd, t_pipex *pipex)
{
	char	*path;

	pipex->cmd_args = ft_split(cmd, "\t\n\v\f\r ");
	if (!pipex->cmd_args)
		pipex_error("split", 1);
	path = get_cmd_path(pipex->cmd_args[0], pipex);
	execve(path, pipex->cmd_args, pipex->env);
	pipex_error("execve", 1);
}

int	execute_first_cmd(t_pipex *pipex)
{
	int		ifd;
	pid_t	pid;

	pid = ft_fork();
	if (pid != 0)
		return (pid);
	ifd = open(pipex->av[1], O_RDONLY);
	if (ifd == -1)
		pipex_error(pipex->av[1], 1);
	close(pipex->pipe_fd[READ]);
	ft_dup2(ifd, STDIN_FILENO);
	ft_dup2(pipex->pipe_fd[WRITE], STDOUT_FILENO);
	close(ifd);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[2], pipex);
	return (-1);
}

int	execute_last_cmd(t_pipex *pipex)
{
	int		ofd;
	pid_t	pid;

	pid = ft_fork();
	if (pid != 0)
		return (pid);
	ofd = open(pipex->av[pipex->ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0664);
	if (ofd == -1)
		pipex_error(pipex->av[pipex->ac - 1], 1);
	ft_dup2(ofd, STDOUT_FILENO);
	close(ofd);
	ft_dup2(pipex->tmp, STDIN_FILENO);
	close(pipex->tmp);
	execute_cmd(pipex->av[pipex->ac - 2], pipex);
	return (-1);
}

int	child_exec(int i, t_pipex *pipex)
{
	ft_dup2(pipex->tmp, STDIN_FILENO);
	close(pipex->tmp);
	ft_dup2(pipex->pipe_fd[WRITE], STDOUT_FILENO);
	close(pipex->pipe_fd[WRITE]);
	close(pipex->pipe_fd[READ]);
	execute_cmd(pipex->av[i + 2], pipex);
	return (1);
}

void	execute_cmds(t_pipex *pipex)
{
	int	i;

	i = 1;
	pipex->pids[0] = execute_first_cmd(pipex);
	pipex->tmp = pipex->pipe_fd[READ];
	if (!pipex->pids)
		pipex_error("malloc", 1);
	close(pipex->pipe_fd[WRITE]);
	while (i < pipex->cmd_nbr - 1)
	{
		pipe(pipex->pipe_fd);
		pipex->pids[i] = ft_fork();
		if (pipex->pids[i] == CHILD)
			child_exec(i, pipex);
		else
		{
			close(pipex->tmp);
			pipex->tmp = pipex->pipe_fd[READ];
			close(pipex->pipe_fd[WRITE]);
		}
		i++;
	}
	pipex->pids[pipex->cmd_nbr - 1] = execute_last_cmd(pipex);
}
