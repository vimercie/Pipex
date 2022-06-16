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

int	pipe_loop(char **argv, t_pipe *p)
{
	if (p->id == 0)
	{
		
	}
}

int	pipe_init(int argc, char **argv)
{
	int		fd[2];
	t_pipe	p;

	// Pipe et fork dans la boucle (écris une seule fois)
	pipe(fd);
	// fd[0];
	// fd[1];
	p.id = fork();
	p.count = argc - 3;
	while (p.count > 0)
	{
		if (p.id == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			exec_cmd();
		}
		else
			pipe_loop(argc, &p);
			// close (fd[1]);
	}
}

// fd[0] non utilisé au tout début
// fd[1] non utilisé à la toute fin