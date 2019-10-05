/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:22:23 by nwispmot          #+#    #+#             */
/*   Updated: 2019/01/19 17:23:21 by nwispmot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	return (i);
}

static	int	ft_del(char **temp)
{
	if (*temp[0] == '\0')
	{
		free(*temp);
		*temp = NULL;
		return (0);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*temp[4096];
	char		*del;
	char		buff[BUFF_SIZE + 1];
	int			ret;

	if (fd < 0 || read(fd, buff, 0) || line == NULL)
		return (-1);
	if (!temp[fd])
		temp[fd] = ft_strnew(0);
	while ((ft_strchr(temp[fd], '\n') == NULL) &&
			(ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		del = temp[fd];
		temp[fd] = ft_strjoin(temp[fd], buff);
		free(del);
	}
	*line = ft_strsub(temp[fd], 0, count(temp[fd]));
	if (ft_del(&temp[fd]) == 0)
		return (0);
	del = temp[fd];
	temp[fd] = ft_strsub(temp[fd], count(temp[fd]) + 1,
			ft_strlen(temp[fd]) - count(temp[fd]));
	free(del);
	return (1);
}
