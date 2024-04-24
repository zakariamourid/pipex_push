/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:12:35 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/24 17:12:36 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**env;
	char	**av;
	int		ac;
	int		cmd_nbr;
	int		ifd;
	int		out_fd;
	int		pipe_fd[2];
	int		*pids;
	char	**cmd_args;
	int		*fds;
	int		tmp;
	char	*cmd_path;
	char	*limiter;
}			t_pipex;

typedef struct t_cmd
{
	char	*cmd;
	char	**cmd_args;
	char	*cmd_path;
}			t_cmd;

ssize_t		ft_write(int fd, const void *buf, size_t count);
int			ft_dup2(int oldfd, int newfd);
pid_t		ft_fork(void);
void		execute_cmd(char *cmd, t_pipex *pipex);
void		execute_cmds(t_pipex *pipex);
void		pipex_error(char *str, int e);
void		clean_exit(int e);
t_pipex		*get_pipex(void);
char		*get_cmd_path(char *cmd, t_pipex *pipex);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char *str, char *charset);
//gnl
char		*ft_strdup(char *str);
char		*ft_strjoin2(char *s1, char *s2);
char		*get_next_line(int fd);
# define BUFFER_SIZE 20
# define WRITE 1
# define READ 0
# define CHILD 0

#endif

