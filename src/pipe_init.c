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


int	pipe_init(int argc, char *argv[], char *envp[])
{
	t_pipe	p;
	char	*buffer;
	char	**cmd;

	buffer = malloc(10 * sizeof(char));
	p.n_cmd = 1;
	(void)argv;
	if (argc == 5)
	{
		pipe(p.fd);
		p.id = fork();
		if (p.id == 0)
		{
			close(p.fd[0]);
			dup2(p.fd[1], 1);
			cmd = exec_cmd(argv[2], envp);
			execve(cmd[0], cmd + 1, envp);
			close(p.fd[1]);
		}
		else
		{
			close(p.fd[1]);
			dup2(p.fd[0], 0);
			waitpid(p.id, NULL, 0);
			read(0, buffer, 25);
			cmd = exec_cmd(argv[3], envp);
			execve(cmd[0], cmd + 1, envp);
			close(p.fd[0]);
		}
	}
	// Multiple pipes
	// if (argc > 5)
	// {
	// 	while (p.n_cmd < argc - 3)
	// 	{
	// 		pipe(p.fd);
	// 		p.id = fork();
	// 		if (p.id == 0)
	// 		{
	// 			close(p.fd[0]);
	// 			dup2(p.fd[1], 1);
	// 			close(p.fd[1]);
	// 			dprintf(1, "I'm the child process");
	// 			// exec_cmd(1ère commande -> argv[p.n_cmd]);
	// 		}
	// 		else
	// 		{
	// 			close(p.fd[1]);
	// 			dup2(p.fd[0], 0);
	// 			close(p.fd[0]);
	// 			waitpid(p.id, NULL, 0);
	// 			read(p.fd[0], buffer, 10);
	// 			dprintf(1, "%s, I'm the parent process", buffer);
	// 			// exec_cmd(2ème commande -> argv[p.n_cmd + 1]);
	// 		}
	// 		p.n_cmd += 1;
	// 	}
	// }
	return (0);
}

// fd[0] non utilisé au tout début
// fd[1] non utilisé à la toute fin