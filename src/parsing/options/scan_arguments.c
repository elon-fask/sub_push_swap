/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_arguments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "options_internal.h"

static t_argument_kind	classify_argument(const char *arg)
{
	if (arg[0] == '\0')
		return (ARGUMENT_OPERAND);
	if (ft_strcmp(arg, "--") == 0)
		return (ARGUMENT_END_OPTIONS);
	if (arg[0] != '-' || arg[1] == '\0')
		return (ARGUMENT_OPERAND);
	if (arg[1] == '-')
		return (ARGUMENT_LONG_OPTION);
	if (ft_isdigit((unsigned char)arg[1]))
		return (ARGUMENT_OPERAND);
	if (ft_isalpha((unsigned char)arg[1]))
		return (ARGUMENT_SHORT_OPTION);
	return (ARGUMENT_INVALID);
}

static int	store_operand(t_parse_context *ctx)
{
	t_operands	*ops;

	ops = &ctx->result->operands;
	ops->values[ops->count] = ctx->argv[ctx->arg_index];
	++ops->count;
	++ctx->arg_index;
	return (0);
}

static int	process_argument(t_parse_context *ctx)
{
	t_argument_kind	kind;

	if (!ctx->options_enabled)
		return (store_operand(ctx));
	kind = classify_argument(ctx->argv[ctx->arg_index]);
	if (kind == ARGUMENT_END_OPTIONS)
	{
		ctx->options_enabled = false;
		++ctx->arg_index;
		return (0);
	}
	if (kind == ARGUMENT_OPERAND)
		return (store_operand(ctx));
	if (kind == ARGUMENT_SHORT_OPTION)
		return (parse_short_options(ctx));
	if (kind == ARGUMENT_LONG_OPTION)
		return (parse_long_option(ctx));
	return (-1);
}

int	scan_arguments(t_parse_context *ctx)
{
	ctx->arg_index = 1;
	ctx->options_enabled = true;
	while (ctx->arg_index < ctx->argc)
	{
		if (process_argument(ctx) != 0)
			return (-1);
	}
	return (0);
}
