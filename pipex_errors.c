/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:12:02 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/24 17:12:03 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_error(char *str, int e)
{
	if (e == 127)
	{
		ft_putstr_fd("pipex: ", 2);
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
