/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:06:46 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/24 23:39:50 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
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
	pipex->cmd_nbr = ac - 2;
	pipex->av = av;
	pipex->env = env;
	pipex->pids = (int *)malloc(sizeof(pid_t) * (pipex->cmd_nbr));
	pipe(pipex->pipe_fd);
	execute_cmds(pipex);
	i = 0;
	while (i < pipex->cmd_nbr)
		waitpid(pipex->pids[i++], &status, 0);
	return (status >> 8);
}
