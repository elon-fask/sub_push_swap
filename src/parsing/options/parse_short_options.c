/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_short_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:00:00 by eallam            #+#    #+#             */
/*   Updated: 2026/11/15 00:00:00 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "options_internal.h"

static const t_option_spec	*find_short_option(
		const t_option_registry *registry, char name)
{
	size_t	i;

	i = 0;
	while (i < registry->count)
	{
		if (registry->specs[i].short_name == name)
			return (&registry->specs[i]);
		++i;
	}
	return (NULL);
}

int	parse_short_options(t_parse_context *ctx)
{
	const char			*arg;
	const t_option_spec	*option;
	size_t				i;

	arg = ctx->argv[ctx->arg_index];
	i = 1;
	while (arg[i])
	{
		option = find_short_option(&ctx->option_registry, arg[i]);
		if (!option || apply_option(ctx, option) != 0)
			return (-1);
		++i;
	}
	++ctx->arg_index;
	return (0);
}
