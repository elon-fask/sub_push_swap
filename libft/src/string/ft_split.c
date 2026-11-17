/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 22:29:32 by eallam            #+#    #+#             */
/*   Updated: 2026/11/16 02:40:34 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*ft_next_word(const char *s, char c, size_t *index)
{
	size_t	start;

	while (s[*index] && s[*index] == c)
		(*index)++;
	start = *index;
	while (s[*index] && s[*index] != c)
		(*index)++;
	return (ft_substr(s, start, *index - start));
}

static void	ft_free_tab(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

static char	**ft_create_tab(const char *s, char c, size_t words)
{
	char	**tab;
	size_t	i;
	size_t	j;

	tab = malloc((words + 1) * sizeof(*tab));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words)
	{
		tab[i] = ft_next_word(s, c, &j);
		if (!tab[i])
		{
			ft_free_tab(tab, i);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_create_tab(s, c, ft_count_words(s, c)));
}
