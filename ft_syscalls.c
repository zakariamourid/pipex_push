/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syscalls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:08:37 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/24 17:08:38 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	ft_write(int fd, const void *buf, size_t count)
{
	ssize_t	len;

	len = write(fd, buf, count);
	if (len == -1)
		pipex_error("write", 1);
	return (len);
}

int	ft_dup2(int oldfd, int newfd)
{
	int	fd;

	fd = 0;
	if (dup2(oldfd, newfd) == -1)
		pipex_error("dup2", 1);
	return (fd);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		pipex_error("fork", 1);
	return (pid);
}
