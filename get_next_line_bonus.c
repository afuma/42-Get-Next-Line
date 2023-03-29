/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:07:55 by edesaint          #+#    #+#             */
/*   Updated: 2023/01/17 15:18:16 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	found_newline(t_list *lst)
{
	t_list	*current;
	int		i;

	if (lst == NULL)
		return (0);
	current = ft_lstlast(lst);
	i = 0;
	while (current->content[i] && current->content[i] != '\n')
		i++;
	if (current->content[i] && current->content[i] == '\n')
		return (1);
	return (0);
}

void	add_to_stash(t_list **lst, char *buf, int readed)
{
	t_list	*new;
	t_list	*last;
	int		i;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = (char *) malloc(sizeof(char) * (readed + 1));
	if (!new->content)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	read_and_stach(int fd, t_list **lst)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*lst) && readed != 0)
	{
		buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		readed = (int) read(fd, buf, BUFFER_SIZE);
		if ((*lst == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add_to_stash(lst, buf, readed);
		free(buf);
		buf = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst[1024];
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (NULL);
	line = NULL;
	read_and_stach(fd, &lst[fd]);
	line = extract_line(lst[fd]);
	if (line)
	{
		if (line[0] == '\0')
		{
			free(line);
			line = NULL;
		}
	}
	if (lst[fd])
	{
		clean_stash(&lst[fd]);
		if (lst[fd]->content[0] == '\0')
			free_stash(&lst[fd], 2);
	}
	return (line);
}
