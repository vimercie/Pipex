/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:17:19 by vimercie          #+#    #+#             */
/*   Updated: 2022/06/16 18:52:30 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../Libft/inc/libft.h"

typedef struct s_pipe
{
	// int fd_in;
	// int fd_out;
	// char	**cmd;
	int	fd[2];
	int	id;
	int	n_cmd;
}				t_pipe;

int		parsing(int argc, char *argv[]);
int		ft_perror(char *s);
int		pipe_init(int argc, char *argv[], char *envp[]);
char	**exec_cmd(char *full_cmd, char *envp[]);

#endif