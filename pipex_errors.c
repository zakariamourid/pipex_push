#include "pipex.h"

static void	free_all(char **data)
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
}
void	clean_exit(int e)
{
	t_pipex	*pipex;

	pipex = get_pipex();
	free_all(pipex->cmd_args);
	exit(e);
}

void	pipex_error(char *str, int e)
{
	if (e == 127)
	{
		ft_putstr_fd("pipex127: ", 2);
		ft_putstr_fd(str, 2);
		if (ft_strchr(str, '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found \n", 2);
	}
	else if (e == 1026)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory \n", 2);
		e = 126;
	}
	else
	{
		ft_putstr_fd("pipex: ", 2);
		perror(str);
	}
	clean_exit(e);
}
