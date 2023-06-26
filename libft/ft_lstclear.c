/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:25:07 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/19 19:09:33 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next_node;

	temp = *lst;
	while (temp)
	{
		next_node = temp->next;
		ft_lstdelone(temp, del);
		temp = next_node;
	}
	*lst = NULL;
}
