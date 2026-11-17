/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 21:08:18 by eallam            #+#    #+#             */
/*   Updated: 2026/11/13 03:40:55 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDS_INTERNAL_H
# define OPERANDS_INTERNAL_H

# include <stddef.h>
# include "operands.h"

int		parse_integer(const char **cursor, int *value);
int		parse_operand(const char *arg, t_stack *stack);

size_t	count_operand_tokens(const t_operands *operands);

#endif /* OPERANDS_INTERNAL_H */
