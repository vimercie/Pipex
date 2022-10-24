/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:23:40 by vimercie          #+#    #+#             */
/*   Updated: 2022/06/16 18:48:41 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	pipe_init(int argc, char *argv[], char *envp[], t_pipe p)
{
	int		fd[2];

	p.n_cmd = 1;
	if (argc == 5)
	{
		pipe(fd);
		p.id1 = fork();
		if (p.id1 == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			dup2(p.fd_infile, 0);
			close(p.fd_infile);
			if (exec_cmd(argv[2], envp) == -1)
				perror_exit(127, argv[0], argv[2]);
		}
		p.id2 = fork();
		if (p.id2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(p.fd_outfile, 1);
			close(p.fd_outfile);
			if (exec_cmd(argv[3], envp) == -1)
				perror_exit(127, argv[0], argv[3]);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(p.id1, NULL, 0);
		waitpid(p.id2, NULL, 0);
	}
	return (0);
}
