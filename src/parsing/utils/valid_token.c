/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:07:50 by junsan            #+#    #+#             */
/*   Updated: 2024/06/28 17:01:51 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_token(t_token *head)
{
	if (!check_quotes_in_tokens(head))
		return (UNCLOSED_QUOTE);
	if (!check_subshell_closed(head))
		return (TOKEN_ERROR);
	if (check_logical_err(head) || check_redir_err(head) || \
		!check_operator_before_after(head))
		return (TOKEN_ERROR);
	return (-1);
}