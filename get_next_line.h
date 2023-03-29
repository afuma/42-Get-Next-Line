/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:21:35 by edesaint          #+#    #+#             */
/*   Updated: 2023/01/17 15:22:44 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

void	add_to_stash(t_list **lst, char *buf, int readed);
void	read_and_stach(int fd, t_list **lst);
int		found_newline(t_list *lst);
char	*get_next_line(int fd);
void	free_stash(t_list **lst, int type_clean);
t_list	*ft_lstlast(t_list *lst);
char	*generate_line(t_list *lst);
char	*extract_line(t_list *lst);
void	clean_stash(t_list **lst);
int		ft_strlen(const char *s);

#endif
