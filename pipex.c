/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:06:46 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/25 17:06:55 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

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

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		status;
	pid_t	p1;
	pid_t	p2;

	if (ac != 5)
	{
		ft_putstr_fd(ERROR_MSG, 2);
		return (1);
	}
	pipex = get_pipex();
	pipex->ac = ac;
	pipex->cmd_nbr = ac - 3;
	pipex->av = av;
	pipex->env = env;
	ft_pipe(pipex->pipe_fd);
	p1 = execute_first_cmd(pipex);
	close(pipex->pipe_fd[WRITE]);
	p2 = execute_last_cmd(pipex);
	close(pipex->pipe_fd[READ]);
	waitpid(p1, &status, 0);
	waitpid(p2, &status, 0);
	clean_exit(status >> 8);
	return (1);
}
