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

int	ft_perror(char *s)
{
	perror(s);
	exit(1);
}

void	file_parsing(t_pipe *p, int argc, char *argv[])
{
	p->fd_outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (access(argv[1], R_OK) == 0)
		p->fd_infile = open(argv[1], O_RDONLY);
	else
		ft_perror(argv[1]);
}

int	parsing(t_pipe *p, int argc, char **argv)
{
	if (argc < 5)
		return (-1);
	file_parsing(p, argc, argv);
	return (1);
}
