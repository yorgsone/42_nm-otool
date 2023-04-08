/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemaroul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 00:12:04 by gemaroul          #+#    #+#             */
/*   Updated: 2018/05/01 10:28:27 by gemaroul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft.h"
# define BUFF_SIZE 32
# define GNL_ERROR -1
# define GNL_FINISHED 0
# define GNL_OK 1
# define READ_ERROR -1

int	get_next_line(int fd, char **line);

#endif
