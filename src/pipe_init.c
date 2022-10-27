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

void	first_c_process(t_pipe *p, int *fd, char *argv[], char *envp[])
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	dup2(p->fd_infile, 0);
	close(p->fd_infile);
	exec_cmd(p, argv[2], envp);
}

void	second_c_process(t_pipe *p, int *fd, char *argv[], char *envp[])
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(p->fd_outfile, 1);
	close(p->fd_outfile);
	exec_cmd(p, argv[3], envp);
}

int	pipe_init(t_pipe *p, int argc, char *argv[], char *envp[])
{
	int		fd[2];

	if (argc == 5)
	{
		pipe(fd);
		p->id1 = fork();
		if (p->id1 == 0)
			first_c_process(p, fd, argv, envp);
		p->id2 = fork();
		if (p->id2 == 0)
			second_c_process(p, fd, argv, envp);
		close(fd[0]);
		close(fd[1]);
		waitpid(p->id1, NULL, 0);
		waitpid(p->id2, NULL, 0);
	}
	return (0);
}
