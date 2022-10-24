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

int	exec_cmd(char *full_cmd, char *envp[])
{
	char	*path;
	char	**args;

	args = ft_split(full_cmd, ' ');
	if (args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
			path = args[0];
		else
			path = NULL;
	}
	else
		path = get_path(args[0], envp);
	if (path == NULL)
		perror_exit(127, "pipex", args[0]);
	execve(path, args, envp);
	return (0);
}
