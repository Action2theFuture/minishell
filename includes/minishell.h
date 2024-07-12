/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:22:19 by junsan            #+#    #+#             */
/*   Updated: 2024/07/12 13:32:23 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h> // opendir, readdir, closedir
# include <errno.h>  // perror
# include <fcntl.h>  // open, read
# include <limits.h>
# include <readline/history.h>
// add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h> // readline
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <stdbool.h>
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free, exit
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/types.h> // stat, lstat, fstat, unlink
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <termios.h>   // isatty, ttyname, ttyslot, tcsetattr, tcgetattr
# include <unistd.h>    // write, access, close, fork, execve, pipe, dup, dup2

# include "minishell_types.h"
# include "parsing.h"
# include "execute.h"
# include "builtin.h"
# include "tokenize.h"
# include "utils.h"

// process_input.c
void					process_input(char *input, t_env *env,
							int *exit_status);

// --------------------------- init --------------------------//
// init_minishell.c
void					init_minishell(char **envp, t_env **env);

// env_init.c
void					add_env(t_env **head, const char *str);
t_env					*env_init(char **envp);
void					env_split(const char *str, char **name, char **content);
char					*valid_required_env_vars(void);

// env_utils.c
size_t					env_size(t_env *head);
void					clear_env(t_env *head);

// increment_shlvl.c
int						increment_shlvl(t_env *env);

// ------------------------ signal ---------------------------//
// handler_signal.c
void					set_signal_handler(void);
void					disable_interrupt_signals(void);

// --------------------------- print --------------------------//
//  prints.c
void					print_token(t_token *head);
void					print_file_list(t_file_list *file_list);
void					print_s(const char *content, const char *str);

//	prints_2.c
void					print_tree(t_ast *root, int depth);

#endif // MINISHELL_H
