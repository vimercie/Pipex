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
	// char	**cmd;
	int fd_infile;
	int fd_outfile;
	int	id1;
	int	id2;
	int	n_cmd;
}				t_pipe;

int		pipe_init(int argc, char *argv[], char *envp[], t_pipe p);
int		exec_cmd(char *full_cmd, char *envp[]);
int		parsing(t_pipe *p, int argc, char *argv[]);
int		perror_exit(int errnum, char *prog_name, char *cmd);

#endif