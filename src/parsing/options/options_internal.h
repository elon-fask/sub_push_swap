/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef OPTIONS_INTERNAL_H
# define OPTIONS_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>
# include "options.h"

typedef enum e_option_action
{
	OPTION_SET_STRATEGY,
	OPTION_ENABLE_BENCHMARK
}						t_option_action;

typedef struct s_option_spec
{
	char				short_name;
	const char			*long_name;
	t_option_action		action;
	t_strategy			strategy;
}						t_option_spec;

typedef struct s_option_registry
{
	const t_option_spec	*specs;
	size_t				count;
}						t_option_registry;

typedef struct s_parse_context
{
	int					argc;
	char				**argv;
	int					arg_index;
	bool				options_enabled;
	t_parse_result		*result;
	t_option_registry	option_registry;
}						t_parse_context;

typedef enum e_argument_kind
{
	ARGUMENT_OPERAND,
	ARGUMENT_SHORT_OPTION,
	ARGUMENT_LONG_OPTION,
	ARGUMENT_END_OPTIONS,
	ARGUMENT_INVALID
}						t_argument_kind;

int						initialize_parse_result(int argc,
							t_parse_result *result);
int						scan_arguments(t_parse_context *context);
int						parse_short_options(t_parse_context *context);
int						parse_long_option(t_parse_context *context);
int						apply_option(t_parse_context *context,
							const t_option_spec *option);

#endif /* OPTIONS_INTERNAL_H */
