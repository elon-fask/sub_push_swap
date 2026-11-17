/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_INTERNAL_H
# define CHUNK_INTERNAL_H

# include <stddef.h>
# include "chunk.h"

typedef struct s_chunk_item
{
	int		value;
	size_t	physical_index;
}			t_chunk_item;

typedef struct s_chunk_state
{
	t_context		*context;
	t_chunk_item	*items;
	size_t			size;
	size_t			width;
	size_t			start;
	size_t			end;
}			t_chunk_state;

void	chunk_rank_values(t_chunk_state *state);
void	chunk_restore_values(t_chunk_state *state);
void	chunk_calculate_width(size_t *width, size_t size);
void	chunk_partition(t_chunk_state *state);
void	chunk_process_range(t_chunk_state *state);
void	chunk_push_back(t_chunk_state *state);

#endif /* CHUNK_INTERNAL_H */
