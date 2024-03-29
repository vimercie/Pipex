/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:13:36 by vimercie          #+#    #+#             */
/*   Updated: 2022/06/16 18:49:21 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_perror(t_pipe *p, int errnum, char **args)
{
	free_tab(args);
	perror_exit(p, errnum, p->err_cmd);
	return ;
}

char	*gather_full_path(char *path, char *cmd)
{
	char	*path_slash;
	char	*full_path;

	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, cmd);
	free(path_slash);
	return (full_path);
}

char	*get_path(char *cmd, char *envp[])
{
	char	*path;
	char	*path_start;
	char	**path_array;
	int		i;

	i = 0;
	while (ft_strstr(envp[i], "PATH=") == NULL)
		i++;
	path_array = ft_split(envp[i], ':');
	path_start = ft_substr(path_array[0], 5, ft_strlen(path_array[0]));
	free(path_array[0]);
	path_array[0] = ft_strdup(path_start);
	free(path_start);
	i = 0;
	path = gather_full_path(path_array[i], cmd);
	while (access(path, X_OK) == -1 && path_array[i])
	{
		i++;
		free(path);
		path = gather_full_path(path_array[i], cmd);
	}
	if (!path_array[i])
		path = NULL;
	return (path);
}

int	exec_cmd(t_pipe *p, char *full_cmd, char *envp[])
{
	char	*path;
	char	**args;
	int		i;

	i = 0;
	if (!full_cmd[0])
		perror_exit(p, 13, full_cmd);
	path = NULL;
	args = ft_split(full_cmd, ' ');
	p->err_cmd = ft_strdup(args[0]);
	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
			path = ft_strdup(args[0]);
		else
			free_perror(p, 2, args);
	}
	else
		path = get_path(args[0], envp);
	if (path == NULL)
		free_perror(p, 127, args);
	execve(path, args, envp);
	return (0);
}
