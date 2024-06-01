/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:47:35 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 17:59:53 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_first_last(char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * (len - 1));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str + 1, len - 1);
	return (new_str);
}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
	|| c == '\f' || c == '\v');
}

bool	is_all_whitespace(const char *str)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (!ft_isspace((unsigned char)*str))
			return (false);
		str++;
	}
	return (true);
}