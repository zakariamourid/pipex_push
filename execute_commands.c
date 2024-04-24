#include "pipex.h"

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
	close(pipex->pipe_fd[READ]);
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
	execute_cmd(pipex->av[pipex->ac - 2], pipex);
	return (-1);
}