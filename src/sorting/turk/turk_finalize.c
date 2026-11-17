/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_finalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turk_internal.h"
#include "sorting_utils.h"

void	turk_rotate_minimum_to_top(t_context *context)
{
	size_t	offset;

	offset = sorting_minimum_offset(&context->stacks.a);
	sorting_rotate_to_offset(context, &context->stacks.a, offset, true);
}
