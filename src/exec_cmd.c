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

char	*add_cmd(char *path, char *cmd)
{
	char	*path_backslash;
	char	*full_path;

	path_backslash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_backslash, cmd);
	free(path_backslash);
	return (full_path);
}

char *get_path(char *cmd, char *envp[])
{
	char	**path_array;
	char	*path;
	char	*path_start;
	int		i;

	i = 0;
	while (ft_strstr(envp[i], "PATH=") == NULL)
		i++;
	path_array = ft_split(envp[i], ':');
	path_start = ft_substr(path_array[0], 5, ft_strlen(path_array[0]));
	path_array[0] = ft_strdup(path_start);
	free(path_start);
	i = 0;
	path = add_cmd(path_array[i], cmd);
	while (access(path, F_OK) == -1 && path_array[i])
	{
		i++;
		free(path);
		path = add_cmd(path_array[i], cmd);
	}
	if (path_array[i] == NULL)
		path = add_cmd(path_array[i], cmd);
	return (path);
}

char	**get_args(char **cmd)
{
	char	**args;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (cmd[i])
	{
		args[i] = ft_strdup(cmd[i]);
		i++;
	}
	cmd[i] = NULL;
	return (args);
}

char	**exec_cmd(char *full_cmd, char *envp[])
{
	int		n_arg;
	char	**cmd;
	char	*path;
	char	**args;

	n_arg = 1;
	cmd = ft_split(full_cmd, ' ');
	while (cmd[n_arg])
		n_arg++;
	path = get_path(cmd[0], envp);
	if (path == NULL)
		ft_perror("pipex");
	args = get_args(cmd);
	cmd[0] = ft_strdup(path);
	if (path != NULL)
		execve(path, args, envp);
	return (cmd);
}