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


int	pipe_init(int argc, char **argv)
{
	t_pipe	p;

	pipe(p.fd);
	while (p.n_cmd < argc - 3)
	{
		p.id = fork();
		p.n_cmd = 0;
		if (p.id == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			exec_cmd();
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1])
			exec_cmd();
		}
	}
}

// fd[0] non utilisé au tout début
// fd[1] non utilisé à la toute fin