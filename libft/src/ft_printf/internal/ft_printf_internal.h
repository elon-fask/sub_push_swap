/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eallam <eallam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 01:56:21 by eallam            #+#    #+#             */
/*   Updated: 2026/11/10 04:26:19 by eallam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include "ft_printf.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef struct s_output
{
	size_t		count;
	int			fd;
	bool		failed;
}				t_output;

typedef struct s_flags
{
	unsigned int	left : 1;
	unsigned int	zero : 1;
	unsigned int	alternate : 1;
	unsigned int	space : 1;
	unsigned int	plus : 1;
}				t_flags;

typedef struct s_format_spec
{
	size_t		width;
	size_t		precision;
	t_flags		flags;
	bool		has_precision;
	char		specifier;
}				t_format_spec;

typedef struct s_context
{
	const char	*cursor;
	va_list		args;
	t_output	output;
}				t_context;

typedef struct s_digit_buffer
{
	char		*data;
	size_t		capacity;
	size_t		length;
}				t_digit_buffer;

typedef struct s_text_repr
{
	const char	*data;
	size_t		length;
}				t_text_repr;

typedef struct s_integer_repr
{
	const char	*digits;
	size_t		digits_len;
	char		sign;
	const char	*prefix;
	size_t		prefix_len;
}				t_integer_repr;

int				ft_process_format(t_context *ctx);
int				ft_process_directive(t_context *ctx);
int				ft_dispatch_conversion(t_context *ctx,
					const t_format_spec *spec);
int				ft_emit_literal(t_context *ctx);

void			ft_parse_flags(t_context *ctx, t_format_spec *spec);
int				ft_parse_decimal(t_context *ctx, size_t *value);
int				ft_parse_width(t_context *ctx, t_format_spec *spec);
int				ft_parse_precision(t_context *ctx, t_format_spec *spec);
int				ft_parse_specifier(t_context *ctx, t_format_spec *spec);
int				ft_parse_directive(t_context *ctx, t_format_spec *spec);

int				ft_convert_char(t_context *ctx, const t_format_spec *spec);
int				ft_convert_string(t_context *ctx, const t_format_spec *spec);
int				ft_convert_signed(t_context *ctx, const t_format_spec *spec);
int				ft_convert_unsigned(t_context *ctx, const t_format_spec *spec);
int				ft_convert_hex(t_context *ctx, const t_format_spec *spec);
int				ft_convert_octal(t_context *ctx, const t_format_spec *spec);
int				ft_convert_binary(t_context *ctx, const t_format_spec *spec);
int				ft_convert_pointer(t_context *ctx, const t_format_spec *spec);
int				ft_convert_percent(t_context *ctx, const t_format_spec *spec);

int				ft_emit_text_field(t_output *out, const t_format_spec *spec,
					const t_text_repr *repr);
int				ft_emit_integer_field(t_output *out, const t_format_spec *spec,
					const t_integer_repr *repr);

int				ft_output_write(t_output *out, const void *buffer,
					size_t length);
int				ft_output_repeat(t_output *out, char c, size_t count);
int				ft_write_all(int fd, const void *buffer, size_t length);

int				ft_utoa_base(uintmax_t value, unsigned int base,
					const char *alphabet, t_digit_buffer *buffer);
size_t			ft_strnlen(const char *s, size_t maxlen);

#endif /* FT_PRINTF_INTERNAL_H */
