/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:06:46 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/25 17:12:29 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

static void	free_all(char **data)
{
	int	i;

	i = -1;
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
	free(pipex->pids);
	exit(e);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	*pipex;
	int		status;
	int		i;

	if (ac < 5)
	{
		ft_putstr_fd(ERROR_MSG, 2);
		return (1);
	}
	pipex = get_pipex();
	pipex->ac = ac;
	pipex->cmd_nbr = ac - 3;
	pipex->av = av;
	pipex->env = env;
	pipex->pids = (int *)malloc(sizeof(pid_t) * (pipex->cmd_nbr));
	execute_cmds(pipex);
	i = 0;
	while (i < pipex->cmd_nbr)
		waitpid(pipex->pids[i++], &status, 0);
	clean_exit(status >> 8 & 0xff);
	return (1);
}
