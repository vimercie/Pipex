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

int	file_parsing(int argc, char *argv[])
{
	// tests oufile
	if (access(argv[argc - 1], F_OK) != 0)
		open(argv[argc - 1], O_RDWR | O_CREAT, 0644);
	else
	{
		if (access(argv[argc - 1], W_OK) == 0)
			open(argv[argc - 1], O_WRONLY);
		else
			ft_perror(argv[argc - 1]);
	}
	// tests infile
	if (access(argv[1], F_OK) != 0)
		ft_perror(argv[1]);
	if (access(argv[1], R_OK) == 0)
		open(argv[1], O_RDONLY);
	else
		ft_perror(argv[1]);
	return (0);
}

int	parsing(int argc, char **argv)
{
	if (argc < 5)
		return (1);
	file_parsing(argc, argv);
	return (0);
}
