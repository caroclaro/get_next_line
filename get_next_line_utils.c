/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelmo-l <cyelmo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:14:43 by cyelmo-l          #+#    #+#             */
/*   Updated: 2026/11/09 19:22:57 by cyelmo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//strlen, but if the str is NULL it returns 0 length
size_t	ft_strlenul(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

//strjoin, but it doesnt check if s1 is NULL, so the first join goes smoothly
char	*ft_strjoingnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s2)
		return (NULL);
	i = 0;
	j = 0;
	new = malloc(ft_strlenul(s1) + ft_strlenul(s2) + 1);
	if (!new)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

//leftovers returns whats left of og after the first \n that encounters
char	*leftovers(char *og)
{
	char	*c;
	int		i;
	int		j;

	if (!og)
		return (NULL);
	i = 0;
	j = 0;
	while (og[i])
	{
		if (og[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	c = malloc(ft_strlenul(og) - i + 1);
	if (!c)
		return (NULL);
	while (og[i])
		c[j++] = og[i++];
	c[j] = 0;
	return (c);
}

//checkcomplete, checks if cad is a full line, ending in /0 or /n
//last is a boolean only used as true in the case the last line is sent
int	checkcomplete(char *cad, int last)
{
	int	i;

	if (!cad)
		return (0);
	i = 0;
	while (cad[i] != '\0')
	{
		if (cad[i] == '\n')
			return (i + 1);
		if (!last && (cad[i + 1] == 0))
			return (-1);
		if (last && (cad[i + 1] == 0))
			return (i + 1);
		i++;
	}
	return (0);
}

//justline returns the first line that it finds in og,
//input last so checkcomplete can be called
char	*justline(char *og, int last)
{
	char	*line;
	int		i;

	if (!og || og[0] == 0)
		return (NULL);
	i = 0;
	line = malloc(checkcomplete(og, last) + 1);
	if (!line)
		return (NULL);
	while (og[i])
	{
		line[i] = og[i];
		if (og[i] == '\n')
			break ;
		i++;
	}
	if (og[i] == '\n')
		line[i + 1] = 0;
	else
		line[i] = 0;
	return (line);
}
