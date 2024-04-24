/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:06:46 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/24 17:06:47 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

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
	pid_t	pid;

	pid = ft_fork();
	if (pid != CHILD)
	{
		return (pid);
	}
	pipex->ifd = open(pipex->av[1], O_RDONLY);
	if (pipex->ifd == -1)
		pipex_error(pipex->av[1], 1);
	ft_dup2(pipex->ifd, STDIN_FILENO);
	ft_dup2(pipex->pipe_fd[WRITE], STDOUT_FILENO);
	close(pipex->ifd);
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
	ft_dup2(pipex->pipe_fd[READ], STDIN_FILENO);
	close(pipex->pipe_fd[READ]);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[pipex->ac - 2], pipex);
	return (-1);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		status;
	pid_t	p1;
	pid_t	p2;

	if (ac != 5)
		return (1);
	pipex = get_pipex();
	pipex->ac = ac;
	pipex->cmd_nbr = ac - 2;
	pipex->av = av;
	pipex->env = env;
	pipex->pids = (int *)malloc(sizeof(pid_t) * (pipex->cmd_nbr));
	pipe(pipex->pipe_fd);
	p1 = execute_first_cmd(pipex);
	p2 = execute_last_cmd(pipex);
	close(pipex->pipe_fd[READ]);
	close(pipex->pipe_fd[WRITE]);
	waitpid(p1, &status, 0);
	waitpid(p2, &status, 0);
	return (status >> 8);
}
