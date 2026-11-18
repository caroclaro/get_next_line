/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelmo-l <cyelmo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:14:25 by cyelmo-l          #+#    #+#             */
/*   Updated: 2026/11/10 13:59:20 by cyelmo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*freeswitch(char **cad, char	*res, int casee)
{
	if (casee == 1)
	{
		free(*cad);
		free(res);
		*cad = NULL;
		return (NULL);
	}
	if (casee == 2)
	{
		free(*cad);
		*cad = NULL;
		return (res);
	}
	return (NULL);
}

static char	*whileout(int fd, char *cad, ssize_t *out)
{
	char	*res;
	char	*temp;

	while ((checkcomplete(cad, 0) < 1) && (*out > 0))
	{
		res = malloc(BUFFER_SIZE + 1);
		if (!res)
			return (freeswitch(&cad, NULL, 2));
		*out = read(fd, res, BUFFER_SIZE);
		if (*out == -1)
			return (freeswitch(&cad, res, 1));
		if (*out == 0)
		{
			free(res);
			break ;
		}
		res[*out] = 0;
		temp = ft_strjoingnl(cad, res);
		if (!temp)
			return (freeswitch(&cad, res, 1));
		free(cad);
		free(res);
		cad = temp;
	}
	return (cad);
}

static char	*linefabric(char **cad, ssize_t out)
{
	char	*temp;
	char	*res;

	if (out == 0)
	{
		res = justline(*cad, 1);
		return (freeswitch(cad, res, 2));
	}
	else
	{
		res = justline(*cad, 0);
		if (!res)
			return (freeswitch(cad, res, 1));
	}
	temp = leftovers(*cad);
	if (!temp)
		return (freeswitch(cad, res, 1));
	free(*cad);
	*cad = temp;
	return (res);
}

//get_next_line the same as the non bonus one, but it uses an array of 1024,
//since this is the max num of fd for gnl, so its able to read multiple 
//documents at once
char	*get_next_line(int fd)
{
	static char	*cad[1024] = {NULL};
	ssize_t		out;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	out = 1;
	cad[fd] = whileout(fd, cad[fd], &out);
	if (!cad[fd] && out != 0)
		return (NULL);
	return (linefabric(&cad[fd], out));
}
