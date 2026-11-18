/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyelmo-l <cyelmo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:15:02 by cyelmo-l          #+#    #+#             */
/*   Updated: 2026/11/10 13:53:01 by cyelmo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

int		checkcomplete(char *cad, int last);
char	*justline(char *og, int last);
char	*leftovers(char *og);
char	*ft_strjoingnl(char const *s1, char const *s2);
size_t	ft_strlenul(const char *s);
char	*get_next_line(int fd);

#endif