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

int	parsing(int argc, char **argv)
{
	int	infile_fd;
	int	outfile_fd;

	if (argc < 5)
		return (1);
	// test existence outfile.
	if (access(argv[argc - 1], F_OK) != 0)
		outfile_fd = open(argv[argc - 1], O_CREAT, S_IRWXO);
	// test accessibilité outfile.
	if (access(argv[argc - 1], W_OK))
		outfile_fd = open(argv[argc - 1]);
	else
	{
		perror("pipex");
		return (1);
	}
	// test existence infile.
	if (access(argv[1], F_OK) != 0)
	{
		perror("pipex");
		return (1);
	}
	if (access(argv[1], R_OK))
		infile_fd = open(argv[1], O_RDONLY);
	else
	{
		perror("pipex");
		return (1);
	}
	return (0);
}
