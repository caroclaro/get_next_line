/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelmo-l <cyelmo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:14:25 by cyelmo-l          #+#    #+#             */
/*   Updated: 2026/11/10 13:48:52 by cyelmo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// freeswitch exists just to optimize and minimize lines of the main fun
// depending on the casee received it frees one val or other
static void	*freeswitch(char **cad, char *res, int casee)
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

// whileout works while there is something left to  
// read or while the line is not complete
// it reads the fd and returns NULL in error case
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

// linefabric create and returns the line that we were trying to read
// it also storages the leftovers on the static cad for the next read
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

// get_next_line checks if the buffer size and the fd are valid if they are it 
// calls whileout and linefabric
char	*get_next_line(int fd)
{
	static char	*cad = NULL;
	ssize_t		out;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	out = 1;
	cad = whileout(fd, cad, &out);
	if (!cad && out != 0)
		return (NULL);
	return (linefabric(&cad, out));
}
