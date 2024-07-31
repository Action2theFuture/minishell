/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:28:11 by junsan            #+#    #+#             */
/*   Updated: 2024/07/31 18:38:30 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit(int status, char **args, char **env, t_info *info)
{
	if (env)
		clear_env_arr(env);
	free_tree(info->root);
	if (args)
		free_args(args);
	if (info->path)
		free(info->path);
	clear_env(info->env);
	exit(status);
}

static void	execute_cmd_with_pipe(\
				char *cmd, char **args, t_info *info, char **env)
{
	if (ft_strlen(cmd) == 4 && ft_strncmp(cmd, "true", 4) == 0)
		cleanup_and_exit(SUCCESS, args, env, info);
	else if (ft_strlen(cmd) == 5 && ft_strncmp(cmd, "false", 5) == 0)
		cleanup_and_exit(FAILURE, args, env, info);
	if (ft_strlen(args[0]) > 2 && args[0][0] == '.' && args[0][1] == '/'
		&& execve(cmd, args, env) == -1)
		cleanup_and_exit(125 + execve_log_error(cmd, errno), args, env, info);
	else if (info->path)
	{
		execve(info->path, args, env);
		free(info->path);
	}
	if (execve(cmd, args, env) == -1)
		cleanup_and_exit(126 + execve_log_error(cmd, errno), args, env, info);
}

void	first_pipe(char *cmd, char **env, char **args, t_info *info)
{
	int		built_in;
	int		(*arr_built_in[7])(\
			const char *, const char **, t_env *);

	if (info->pid == 0)
	{
		dup2(info->tmp_pipe[2], STDOUT_FILENO);
		if (info->tmp_pipe[0] != -1)
			close(info->tmp_pipe[0]);
		close(info->tmp_pipe[1]);
		close(info->tmp_pipe[2]);
		init_builtin(arr_built_in);
		built_in = handler_builtin(cmd);
		if (built_in != NONE)
		{
			if (built_in == EXIT)
				cleanup_and_exit(0, args, env, info);
			cleanup_and_exit(arr_built_in[built_in](\
			(const char *)cmd, (const char **)args, info->env), \
					args, env, info);
		}
		else
			execute_cmd_with_pipe(cmd, args, info, env);
	}
}

void	middle_pipe(char *cmd, char **env, char **args, t_info *info)
{
	int		built_in;
	int		(*arr_built_in[7])(\
			const char *, const char **, t_env *);

	if (info->pid == 0)
	{
		dup2(info->tmp_pipe[0], STDIN_FILENO);
		dup2(info->tmp_pipe[2], STDOUT_FILENO);
		close(info->tmp_pipe[0]);
		close(info->tmp_pipe[1]);
		close(info->tmp_pipe[2]);
		init_builtin(arr_built_in);
		built_in = handler_builtin(cmd);
		if (built_in != NONE)
		{
			if (built_in == EXIT)
				cleanup_and_exit(0, args, env, info);
			cleanup_and_exit(arr_built_in[built_in](\
			(const char *)cmd, (const char **)args, info->env), \
					args, env, info);
		}
		else
			execute_cmd_with_pipe(cmd, args, info, env);
	}
}

void	last_pipe(char *cmd, char **env, char **args, t_info *info)
{
	int		status;
	int		built_in;
	int		(*arr_built_in[7])(\
			const char *, const char **, t_env *);

	if (info->pid == 0)
	{
		dup2(info->tmp_pipe[0], STDIN_FILENO);
		close(info->tmp_pipe[0]);
		close(info->tmp_pipe[1]);
		close(info->tmp_pipe[2]);
		init_builtin(arr_built_in);
		built_in = handler_builtin(cmd);
		if (built_in != NONE)
		{
			if (built_in == EXIT)
				cleanup_and_exit(0, args, env, info);
			status = (arr_built_in[built_in](\
			(const char *)cmd, (const char **)args, info->env));
			cleanup_and_exit(status, args, env, info);
		}
		else
			execute_cmd_with_pipe(cmd, args, info, env);
	}
}
