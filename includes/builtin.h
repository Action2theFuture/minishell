/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:14:06 by junsan            #+#    #+#             */
/*   Updated: 2024/07/12 13:24:25 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell_types.h"
// built_in.c
void					init_builtin(int (*func[])(const char *, const char **,
								t_env *));
int						handler_builtin(const char *cmd);

// file_dir_operations.c
int						change_dir(const char *path, t_env *lst);
bool					get_cur_dir(void);
bool					file_exist(const char *filename);
void					list_dir(const char *dirname);

// ft_cd.c
void					ist_swap(t_env *a);
int						ft_cd(const char *cmd, const char **args, t_env *list);

// ft_echo.c
int						ft_echo(const char *cmd, const char **args,
							t_env *list);

// ft_env.c
void					add_builtin_node(t_env **head, char *name,
							char *content);
void					printf_env(t_env *list);
int						ft_env(const char *cmd, const char **args, t_env *list);

// void	env_split(const char *str, char **name, char **content);

// ft_exit.c
int						ft_exit(const char *cmd, const char **args,
							t_env *list);

// ft_export.c
void					env_split(const char *str, char **name, char **content);

// void			ft_export_add(char *var, char **arg);
// void			ft_export_show(t_env *env);
int						ft_export(\
		const char *cmd, const char **args, t_env *list);
// t_env			*sort_list(t_env *env);

// ft_pwd.c
int						ft_pwd(const char *cmd, const char **args, t_env *list);

// ft_unset.c
int						ft_unset(const char *cmd, const char **args,
							t_env *list);

// subshell_utils.c
char					*remove_nested_subshell(t_token **token);
#endif // BUILTIN_H
