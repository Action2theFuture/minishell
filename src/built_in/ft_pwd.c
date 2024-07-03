/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:59:35 by junsan            #+#    #+#             */
/*   Updated: 2024/07/03 18:19:45 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(const char *cmd, const char **args, t_env *list)
{
	char	*print;

	(void)cmd;
	(void)list;
	if (args[1])
	{
		printf("kashell: pwd: %s: invalid option\n", args[1]);
		printf("pwd: usage: pwd [-LP]\n");
		return (FAILURE);
	}
	print = getcwd(NULL, 0);
	if (!print)
	{
		fd_log_error("pwd", NULL, strerror(errno));
		return (FAILURE);
	}
	if (write(1, print, strlen(print)) == -1)
		return (FAILURE);
	if (write(1, "\n", 1) == -1)
		return (0);
	return (SUCCESS);
}
