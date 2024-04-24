#include "pipex.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>

void	free_data(char **data, char *cmd)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	free(cmd);
}
char	*ft_look_in_path(char *cmd, char *path)
{
	char	*cmd_path;
	char	**paths;
	char	*cmd2;
	int		i;

	i = -1;
	if (!cmd || !path)
		pipex_error(cmd, 127);
	paths = ft_split(path + 5, ":");
	cmd2 = ft_strjoin("/", cmd);
	if (!paths || !cmd2)
		pipex_error("split", 1);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd2);
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
				return (free_data(paths, cmd2), cmd_path);
			else
				pipex_error(cmd_path, 126);
		}
		free(cmd_path);
	}
	return (free_data(paths, cmd2), pipex_error(cmd, 127), NULL);
}

void	check_dir(char *cmd)
{
	int	fd;

	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
		pipex_error(cmd, 1026);
	close(fd);
}

char	*get_cmd_path(char *cmd, t_pipex *pipex)
{
	char	*path;

	path = NULL;
	while (*pipex->env)
	{
		if (!ft_strncmp(*pipex->env, "PATH=", 5))
			path = *pipex->env;
		pipex->env++;
	}
	if (!cmd || !*cmd)
		clean_exit(0);
	if (ft_strchr(cmd, '/') || !path)
	{
		if (!access(cmd, F_OK))
		{
			check_dir(cmd);
			if (!access(cmd, X_OK))
				return (cmd);
			else
				pipex_error(cmd, 126);
		}
		pipex_error(cmd, 127);
	}
	return (ft_look_in_path(cmd, path));
}
