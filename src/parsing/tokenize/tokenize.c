/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:39:22 by junsan            #+#    #+#             */
/*   Updated: 2024/06/21 20:43:49 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(const char *input, t_token **tokens)
{
	const char	*start;
	char		in_quote;
	int			depth;

	start = input;
	in_quote = 0;
	depth = 0;
	while (*input)
	{
		handle_quotes(&input, &in_quote, &start, tokens);
		if (!in_quote)
		{
			if (*input == '(')
				handle_open_subshell(&input, &depth, &start, tokens);
			else if (depth > 0 && *input == ')')
				handle_close_subshell(&input, &depth, &start, tokens);
		}
		if (!in_quote && depth == 0)
			handle_operators_and_spaces(&input, &start, tokens);
		input++;
	}
	if (input > start)
		add_token(tokens, start, input - start);
}
