/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelmo-l <cyelmo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:14:43 by cyelmo-l          #+#    #+#             */
/*   Updated: 2026/11/09 19:27:18 by cyelmo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strjoingnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*cambiar;

	if (!s2)
		return (NULL);
	i = 0;
	j = 0;
	cambiar = malloc(ft_strlenul(s1) + ft_strlenul(s2) + 1);
	if (!cambiar)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		cambiar[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		cambiar[i] = s2[j];
		i++;
		j++;
	}
	cambiar[i] = '\0';
	return (cambiar);
}

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
