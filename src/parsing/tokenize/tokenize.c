/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:39:22 by junsan            #+#    #+#             */
/*   Updated: 2024/07/01 20:07:36 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(const char *input, t_token **tokens)
{
	const char	*start;
	int			depth;

	start = input;
	depth = 0;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			handle_quotes(&input, &start, tokens);
		else if (*input == '(')
			handle_open_subshell(&input, &depth, &start, tokens);
		else if (depth > 0 && *input == ')')
			handle_close_subshell(&input, &depth, &start, tokens);
		else
		{
			handle_operators_and_spaces(&input, &start, tokens);
			if (*input == '(')
			{
				add_token(tokens, "(", 1);
				depth++;
			}
			else if (depth > 0 && *input == ')')
			{
				add_token(tokens, ")", 1);
				depth--;
			}
		}
		if (*input)
			input++;
	}
	if (input > start)
		add_token(tokens, start, input - start);
}
