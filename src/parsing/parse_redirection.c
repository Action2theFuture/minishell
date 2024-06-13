/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:25:32 by junsan            #+#    #+#             */
/*   Updated: 2024/06/13 19:35:01 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_io_redirection(t_token **token, t_ast **node)
{
	t_ast	*io_redirection_node;
	t_ast	*right;

	right = NULL;
	printf("io_redirection >> \n");
	if (*token && (*token)->type == REDIRECTION)
	{
		printf("token data : %s\n", (*token)->data);
		io_redirection_node = new_node(NULL, IO);
		if (!io_redirection_node)
			return (false);
		*node = new_node((*token)->data, get_type_redir((*token)->data));
		*token = (*token)->next;
		if (*token && (*token)->type == CMD)
		{
			right = new_node((*token)->data, (*token)->type);
			*token = (*token)->next;
		}
		io_redirection_node->left = *node;
		io_redirection_node->right = right;
		*node = io_redirection_node;
	}
	return (true);
}

bool	parse_redirection(t_token **token, t_ast **node)
{
	t_ast	*redirection_node;
	t_ast	*left;

	printf("redirection >> \n");
	printf("token data : %s\n", (*token)->data);
	left = NULL;
	redirection_node = new_node(NULL, REDIRECTION);
	if (!redirection_node)
		return (false);
	if (*token && (*token)->type == REDIRECTION)
	{
		parse_io_redirection(token, &left);
		redirection_node->left = left;
		*node = redirection_node;
	}
	return (true);
}
