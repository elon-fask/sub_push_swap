/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef OPTIONS_H
# define OPTIONS_H

# include <stdbool.h>
# include <stddef.h>

typedef enum e_strategy
{
	STRATEGY_ADAPTIVE,
	STRATEGY_SIMPLE,
	STRATEGY_MEDIUM,
	STRATEGY_COMPLEX
}						t_strategy;

typedef struct s_program_options
{
	t_strategy			strategy;
	bool				strategy_explicit;
	bool				benchmark_enabled;
}						t_program_options;

typedef struct s_operands
{
	char				**values;
	size_t				count;
	size_t				capacity;
}						t_operands;

typedef struct s_parse_result
{
	t_program_options	options;
	t_operands			operands;
}						t_parse_result;

int						parse_options(int argc, char **argv,
							t_parse_result *result);
void					destroy_parse_result(t_parse_result *result);

#endif /* OPTIONS_H */
