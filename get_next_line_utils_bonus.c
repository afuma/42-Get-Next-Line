/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:43:50 by edesaint          #+#    #+#             */
/*   Updated: 2023/01/17 14:56:13 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current && current->next)
		current = current->next;
	return (current);
}

char	*generate_line(t_list *lst)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!lst)
		return (NULL);
	while (lst)
	{
		while (lst->content[i] && lst->content[i] != '\n')
			i++;
		if (lst->content[i] && lst->content[i] == '\n')
			i++;
		len += i;
		i = 0;
		lst = lst->next;
	}
	line = (char *) malloc(sizeof(char) * (len + 1));
	return (line);
}

char	*extract_line(t_list *lst)
{
	char	*line;
	int		i;
	int		len;

	line = generate_line(lst);
	if (!line)
		return (NULL);
	i = 0;
	len = 0;
	while (lst)
	{
		while (lst->content[i] && lst->content[i] != '\n')
		{
			line[len + i] = lst->content[i];
			i++;
		}
		if (lst->content[i] && lst->content[i] == '\n')
			line[len + i++] = '\n';
		len += i;
		i = 0;
		lst = lst->next;
	}
	line[len] = '\0';
	return (line);
}

void	free_stash(t_list **lst, int type_clean)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	if (type_clean == 1)
	{
		while (current != NULL && current->next != NULL)
		{
			free(current->content);
			current->content = NULL;
			next = current->next;
			free(current);
			current = NULL;
			current = next;
		}
	}
	if (type_clean == 2)
	{
		free(current->content);
		current->content = NULL;
		free(current);
		current = NULL;
	}
	*lst = current;
}

void	clean_stash(t_list **lst)
{
	char	*buf;
	int		len_buf;
	int		i;
	int		l;

	i = 0;
	l = 0;
	free_stash(lst, 1);
	while ((*lst)->content[i] && (*lst)->content[i] != '\n')
		i++;
	if ((*lst)->content[i] && (*lst)->content[i] == '\n')
		i++;
	len_buf = ft_strlen((*lst)->content);
	buf = (char *) malloc(sizeof(char) * (len_buf - i + 1));
	len_buf -= i;
	if (!buf)
		return ;
	while ((*lst)->content[i])
		buf[l++] = (*lst)->content[i++];
	buf[l] = '\0';
	free_stash(lst, 2);
	add_to_stash(lst, buf, len_buf);
	free(buf);
	buf = NULL;
}
