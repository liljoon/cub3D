/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yham <yham@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:30:04 by yham              #+#    #+#             */
/*   Updated: 2023/06/25 21:31:26 by yham             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

char	*get_next_line(int fd);

int		gnl_strlen(char *s);
char	*gnl_strdup(char *src);
char	*gnl_strjoin(char *s1, char *s2);

#endif