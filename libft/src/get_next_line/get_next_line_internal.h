/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:42:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/12 20:50:48 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_INTERNAL_H
# define GET_NEXT_LINE_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>

# define LIBFT_GET_NEXT_LINE_BUFFER_SIZE 4096

typedef enum e_gnl_status
{
	GNL_ERROR = -1,
	GNL_NEED_INPUT,
	GNL_LINE_READY
}				t_gnl_status;

typedef struct s_gnl_state
{
	char	*data;
	size_t	capacity;
	size_t	read_pos;
	size_t	scan_pos;
	size_t	data_end;
	bool	eof;
	bool	failed;
}			t_gnl_state;

bool		ensure_buffer_space(t_gnl_state *state, size_t incoming_bytes);
t_gnl_state	*get_next_line_state(void);
void		reset_gnl_state(t_gnl_state *state);

#endif /* GET_NEXT_LINE_INTERNAL_H */
