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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	return ;
}

int	perror_exit(t_pipe *p, int errnum, char *cmd)
{
	write(2, p->prog_name, ft_strlen(p->prog_name));
	write(2, ": ", 2);
	if (errnum != 0)
	{
		if (errnum == 127)
			write(2, "command not found", 17);
		else if (errnum == 7)
			write(2, "invalid number of arguments", 27);
		else
			write(2, strerror(errnum), ft_strlen(strerror(errnum)));
	}
	if (cmd != NULL)
	{
		write(2, ": ", 2);
		write(2, cmd, ft_strlen(cmd));
	}
	write(2, "\n", 1);
	free(p->err_cmd);
	free(p->prog_name);
	exit(errnum);
}

void	file_parsing(t_pipe *p, char *argv[])
{
	if (!argv[1][0] || access(argv[1], F_OK) != 0)
		perror_exit(p, 2, argv[1]);
	else if (access(argv[1], R_OK) != 0)
		perror_exit(p, 13, argv[1]);
	else
		p->fd_infile = open(argv[1], O_RDONLY);
	if (!argv[4][0])
		perror_exit(p, 2, argv[4]);
	else if (access(argv[4], F_OK) == 0 && access(argv[4], W_OK) != 0)
		perror_exit(p, 13, argv[4]);
	else
		p->fd_outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

int	parsing(t_pipe *p, int argc, char **argv)
{
	p->prog_name = ft_substr(argv[0], 2, ft_strlen(argv[0]) - 2);
	if (argc != 5)
		perror_exit(p, 127, NULL);
	file_parsing(p, argv);
	return (1);
}
