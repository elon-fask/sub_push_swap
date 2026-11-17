CC              := cc
AR              := ar
ARFLAGS         := rcs
NAME            := libft.a

CFLAGS          := -Wall -Wextra -Werror
CPPFLAGS        := -Iinclude -Isrc/ft_printf/internal -Isrc/get_next_line

BUILD_DIR       := build

HEADERS         := include/libft.h \
                   include/ft_printf.h \
                   include/get_next_line.h \
                   src/ft_printf/internal/ft_printf_internal.h \
                   src/get_next_line/get_next_line_internal.h

DEPFLAGS        := -MMD -MP

RESET           := \033[0m
BOLD            := \033[1m
DIM             := \033[2m

BLACK           := \033[30m
RED             := \033[31m
GREEN           := \033[32m
YELLOW          := \033[33m
BLUE            := \033[34m
MAGENTA         := \033[35m
CYAN            := \033[36m
WHITE           := \033[37m

BRIGHT_BLACK    := \033[90m
BRIGHT_RED      := \033[91m
BRIGHT_GREEN    := \033[92m
BRIGHT_YELLOW   := \033[93m
BRIGHT_BLUE     := \033[94m
BRIGHT_MAGENTA  := \033[95m
BRIGHT_CYAN		:= \033[96m
BRIGHT_WHITE	:= \033[97m

TAG_CC          := $(BOLD)$(CYAN)
TAG_AR          := $(BOLD)$(GREEN)
TAG_MKDIR       := $(BOLD)$(BLUE)
TAG_CLEAN       := $(BOLD)$(YELLOW)
TAG_FCLEAN      := $(BOLD)$(RED)

LIBFT_CHARACTER := src/character/ft_isalnum.c \
                   src/character/ft_isalpha.c \
                   src/character/ft_isascii.c \
                   src/character/ft_isdigit.c \
                   src/character/ft_isspace.c \
                   src/character/ft_isprint.c \
                   src/character/ft_tolower.c \
                   src/character/ft_toupper.c

LIBFT_CONVERSION := src/conversion/ft_atoi.c \
                    src/conversion/ft_itoa.c

LIBFT_IO        := src/io/ft_putchar_fd.c \
                   src/io/ft_putendl_fd.c \
                   src/io/ft_putnbr_fd.c \
                   src/io/ft_putstr_fd.c

LIBFT_LIST      := src/list/ft_lstnew.c \
                   src/list/ft_lstadd_front.c \
                   src/list/ft_lstsize.c \
                   src/list/ft_lstlast.c \
                   src/list/ft_lstadd_back.c \
                   src/list/ft_lstdelone.c \
                   src/list/ft_lstclear.c \
                   src/list/ft_lstiter.c \
                   src/list/ft_lstmap.c

LIBFT_MEMORY    := src/memory/ft_bzero.c \
                   src/memory/ft_calloc.c \
                   src/memory/ft_memchr.c \
                   src/memory/ft_memcmp.c \
                   src/memory/ft_memcpy.c \
                   src/memory/ft_memmove.c \
                   src/memory/ft_memset.c

LIBFT_STRING    := src/string/ft_split.c \
                   src/string/ft_strchr.c \
                   src/string/ft_strdup.c \
                   src/string/ft_striteri.c \
                   src/string/ft_strjoin.c \
                   src/string/ft_strlcat.c \
                   src/string/ft_strlcpy.c \
                   src/string/ft_strlen.c \
                   src/string/ft_strmapi.c \
                   src/string/ft_strcmp.c \
                   src/string/ft_strncmp.c \
                   src/string/ft_strnstr.c \
                   src/string/ft_strrchr.c \
                   src/string/ft_strtrim.c \
                   src/string/ft_substr.c

LIBFT_SRCS      := $(LIBFT_CHARACTER) $(LIBFT_CONVERSION) \
                   $(LIBFT_IO) $(LIBFT_LIST) \
                   $(LIBFT_MEMORY) $(LIBFT_STRING)



GNL_DIR = src/get_next_line

GNL_SRCS = \
	$(GNL_DIR)/get_next_line.c \
	$(GNL_DIR)/get_next_line_state.c \
	$(GNL_DIR)/get_next_line_utils.c


PRINTF_DIR      := src/ft_printf

PRINTF_API      := $(PRINTF_DIR)/api/ft_printf.c \
                   $(PRINTF_DIR)/api/ft_dprintf.c \
                   $(PRINTF_DIR)/api/ft_vdprintf.c

PRINTF_CORE     := $(PRINTF_DIR)/core/ft_process_format.c \
                   $(PRINTF_DIR)/core/ft_process_directive.c \
                   $(PRINTF_DIR)/core/ft_dispatch_conversion.c \
                   $(PRINTF_DIR)/core/ft_emit_literal.c

PRINTF_PARSING  := $(PRINTF_DIR)/parsing/ft_parse_directive.c \
                   $(PRINTF_DIR)/parsing/ft_parse_flags.c \
                   $(PRINTF_DIR)/parsing/ft_parse_width.c \
                   $(PRINTF_DIR)/parsing/ft_parse_precision.c \
                   $(PRINTF_DIR)/parsing/ft_parse_specifier.c \
                   $(PRINTF_DIR)/parsing/ft_parse_decimal.c

PRINTF_CONV     := $(PRINTF_DIR)/conversions/ft_convert_char.c \
                   $(PRINTF_DIR)/conversions/ft_convert_string.c \
                   $(PRINTF_DIR)/conversions/ft_convert_signed.c \
                   $(PRINTF_DIR)/conversions/ft_convert_unsigned.c \
                   $(PRINTF_DIR)/conversions/ft_convert_hex.c \
                   $(PRINTF_DIR)/conversions/ft_convert_octal.c \
                   $(PRINTF_DIR)/conversions/ft_convert_binary.c \
                   $(PRINTF_DIR)/conversions/ft_convert_pointer.c \
                   $(PRINTF_DIR)/conversions/ft_convert_percent.c

PRINTF_FORMAT   := $(PRINTF_DIR)/formatting/ft_emit_text_field.c \
                   $(PRINTF_DIR)/formatting/ft_emit_integer_field.c

PRINTF_OUTPUT   := $(PRINTF_DIR)/output/ft_output_write.c \
                   $(PRINTF_DIR)/output/ft_output_repeat.c \
                   $(PRINTF_DIR)/output/ft_write_all.c

PRINTF_UTILS    := $(PRINTF_DIR)/utils/ft_utoa_base.c \
                   $(PRINTF_DIR)/utils/ft_strnlen.c

PRINTF_SRCS     := $(PRINTF_API) $(PRINTF_CORE) $(PRINTF_PARSING) \
                   $(PRINTF_CONV) $(PRINTF_FORMAT) \
                   $(PRINTF_OUTPUT) $(PRINTF_UTILS)

SRCS            := $(LIBFT_SRCS) $(GNL_SRCS) $(PRINTF_SRCS)

OBJS            := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS            := $(OBJS:.o=.d)

OBJ_DIRS        := $(sort $(dir $(OBJS)))

.DEFAULT_GOAL   := all

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) Makefile
	@rm -f $@
	@$(AR) $(ARFLAGS) $@ $(OBJS)
	@printf "$(TAG_AR)[AR]$(RESET) Creating $(DIM)%s$(RESET)\n" "$@"

$(OBJ_DIRS):
	@mkdir -p $@
	@printf "$(TAG_MKDIR)[MKDIR]$(RESET) Creating $(DIM)%s$(RESET)\n" "$@"

$(BUILD_DIR)/%.o: src/%.c | $(OBJ_DIRS)
	@printf "$(TAG_CC)[CC]$(RESET) Compiling $(DIM)%s$(RESET)\n" "$<"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) \
		-MF $(@:.o=.d) -MT $@ -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@printf "$(TAG_CLEAN)[CLEAN]$(RESET) Removing build directory\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(TAG_FCLEAN)[FCLEAN]$(RESET) Removing $(DIM)%s$(RESET)\n" "$(NAME)"

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.DELETE_ON_ERROR:

.PHONY: all clean fclean re
