/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimercie <vimercie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:40:43 by vimercie          #+#    #+#             */
/*   Updated: 2022/06/16 18:38:44 by vimercie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/pipex.h"

int	error_check(int argc, char **argv)
{
	if (argc < 5)
		return (1);
	if (!access(argv[0], F_OK))
		return (0);
}
