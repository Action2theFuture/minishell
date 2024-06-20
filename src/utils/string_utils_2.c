/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:29:43 by junsan            #+#    #+#             */
/*   Updated: 2024/06/20 21:30:44 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *str, size_t n)
{
    size_t	len;
	char 	*new_str;

	len = ft_strlen(str);
	if (len > n)
		len = n;

    new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, len + 1);
	return new_str;
}

char	*trim_whitespace(const char *str)
{
	const char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	return (ft_substr(str, 0, end - str + 1));
}

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

static void	remove_quotes(char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = NULL;
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') \
					|| (str[0] == '\'' && str[len - 1] == '\'')))
		new_str = trim_first_last(str);
	if (new_str != NULL)
	{
		free(str);
		str = new_str;
	}
}

void	remove_quotes_from_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		remove_quotes(args[i]);
}

void	remove_outer_parentheses(char **str)
{
	int		len;

	len = ft_strlen(*str);
	if (len >= 2 && (*str)[0] == '(' && (*str)[len - 1] == ')')
	{
		ft_memmove(*str, *str + 1, len - 2);
		(*str)[len - 2] = '\0';
	}
}
