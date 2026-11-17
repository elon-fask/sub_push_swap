/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 21:04:44 by eallam            #+#    #+#             */
/*   Updated: 2026/11/09 23:45:55 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_content(void *content, void (*del)(void *))
{
	if (content)
		del(content);
}

static void	ft_append_node(t_list **head, t_list **tail, t_list *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tail;
	t_list	*node;
	void	*content;

	if (!f || !del)
		return (NULL);
	new_list = NULL;
	tail = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			ft_free_content(content, del);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_append_node(&new_list, &tail, node);
		lst = lst->next;
	}
	return (new_list);
}
