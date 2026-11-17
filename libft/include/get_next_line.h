/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:42:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 20:48:05 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>

char	*get_next_line(int fd);
void	get_next_line_cleanup(void);
bool	get_next_line_has_error(void);

#endif /* GET_NEXT_LINE_H */
