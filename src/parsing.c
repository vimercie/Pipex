/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:33:10 by vimercie          #+#    #+#             */
/*   Updated: 2022/06/16 18:38:12 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	perror_exit(int errnum, char *prog_name, char *cmd)
{
	write(2, prog_name, ft_strlen(prog_name));
	write(2, ": ", 2);
	if (errnum == 127)
		write(2, "command not found", 17);
	else if (errnum == 7)
		write(2, "invalid number of arguments", 27);
	else
		write(2, strerror(errnum), ft_strlen(strerror(errnum)));
	if (cmd != NULL)
	{
		write(2, ": ", 2);
		write(2, cmd, ft_strlen(cmd));
	}
	write(2, "\n", 1);
	exit(errnum);
}

void	file_parsing(t_pipe *p, int argc, char *argv[])
{
	if (access(argv[1], R_OK) != 0)
		perror_exit(13, argv[0], argv[1]);
	else
		p->fd_infile = open(argv[1], O_RDONLY);
	if (access(argv[argc - 1], W_OK) != 0 && access(argv[argc - 1], F_OK) == 0)
		perror_exit(13, argv[0], argv[argc - 1]);
	else
		p->fd_outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

int	parsing(t_pipe *p, int argc, char **argv)
{
	if (argc != 5)
		perror_exit(7, "pipex", NULL);
	file_parsing(p, argc, argv);
	return (1);
}

// QD TU LIS SUR UN PIPE CA EFFACE DEDANS AUTOMATIQUEMENT