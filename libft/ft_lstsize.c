/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isunwoo <isunwoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:55:32 by isunwoo           #+#    #+#             */
/*   Updated: 2022/07/19 18:53:46 by isunwoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		cnt;

	cnt = 0;
	temp = lst;
	while (temp)
	{
		cnt++;
		temp = temp->next;
	}
	return (cnt);
}
