CC              := cc
CFLAGS          := -Wall -Wextra -Werror
CPPFLAGS        := -Ilibft/include \
                   -Isrc -Isrc/bonus \
                   -Isrc/parsing/operands -Isrc/parsing/options \
                   -Isrc/stack -Isrc/stats -Isrc/operations \
                   -Isrc/sorting/utils -Isrc/sorting/selection \
                   -Isrc/sorting/small_sort \
                   -Isrc/sorting/chunk -Isrc/sorting/turk
DEPFLAGS        := -MMD -MP

NAME            := push_swap
CHECKER         := checker
LIBFT_DIR       := libft
LIBFT           := $(LIBFT_DIR)/libft.a
LIBFT_INPUTS    := $(shell find $(LIBFT_DIR)/src $(LIBFT_DIR)/include \
	-type f \( -name '*.c' -o -name '*.h' \)) $(LIBFT_DIR)/Makefile
BUILD_DIR       := build

RESET           := \033[0m
BOLD            := \033[1m
DIM             := \033[2m
CYAN            := \033[36m
GREEN           := \033[32m
YELLOW          := \033[33m
RED             := \033[31m
BLUE            := \033[34m

TAG_CC          := $(BOLD)$(CYAN)
TAG_MKDIR       := $(BOLD)$(BLUE)
TAG_CLEAN       := $(BOLD)$(YELLOW)
TAG_FCLEAN      := $(BOLD)$(RED)
TAG_LD          := $(BOLD)$(GREEN)

COMMON_SOURCES  := \
	src/parsing/parse_result.c \
	src/parsing/operands/count_operand_tokens.c \
	src/parsing/operands/parse_integer.c \
	src/parsing/operands/parse_operand.c \
	src/parsing/operands/parse_operands.c \
	src/stack/stack_pop_top.c \
	src/stack/stack_push_top.c \
	src/stack/stack_reverse_rotate.c \
	src/stack/stack_rotate.c \
	src/stack/stack_swap_top.c \
	src/stack/initialize_stacks.c \
	src/stack/destroy_stacks.c \
	src/sorting/utils/stack_lookup.c \
	src/sorting/is_sorted.c

PUSH_SWAP_SOURCES := \
	src/main.c \
	src/orchestrator.c \
	src/orchestrator_dispatch.c \
	src/sorting/disorder_ratio.c \
	src/sorting/utils/rotate_to_offset.c \
	src/sorting/utils/rotation_distance.c \
	src/operations/operation_push.c \
	src/operations/operation_reverse_rotate.c \
	src/operations/operation_rotate.c \
	src/operations/operation_swap.c \
	src/parsing/options/apply_option.c \
	src/parsing/options/parse_long_option.c \
	src/parsing/options/parse_options.c \
	src/parsing/options/parse_short_options.c \
	src/parsing/options/scan_arguments.c \
	src/sorting/selection/selection_sort.c \
	src/sorting/small_sort/small_sort.c \
	src/sorting/small_sort/small_sort_utils.c \
	src/sorting/small_sort/sort_three.c \
	src/sorting/small_sort/sort_five.c \
	src/sorting/chunk/chunk_sort.c \
	src/sorting/chunk/chunk_index.c \
	src/sorting/chunk/chunk_partition.c \
	src/sorting/chunk/chunk_restore.c \
	src/sorting/turk/turk_cost.c \
	src/sorting/turk/turk_cost_utils.c \
	src/sorting/turk/turk_target_a.c \
	src/sorting/turk/turk_target_b.c \
	src/sorting/turk/turk_move.c \
	src/sorting/turk/turk_small_sort.c \
	src/sorting/turk/turk_finalize.c \
	src/sorting/turk/turk_sort.c \
	src/stats/stats.c \
	src/stats/print_benchmark.c

CHECKER_SOURCES := \
	src/bonus/main_bonus.c \
	src/bonus/checker_dispatch_bonus.c \
	src/bonus/checker_loop_bonus.c \
	src/bonus/execute_push_bonus.c \
	src/bonus/execute_reverse_rotate_bonus.c \
	src/bonus/execute_rotate_bonus.c \
	src/bonus/execute_swap_bonus.c

COMMON_OBJECTS    := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(COMMON_SOURCES))
PUSH_SWAP_OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(PUSH_SWAP_SOURCES))
CHECKER_OBJECTS   := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(CHECKER_SOURCES))
ALL_OBJECTS       := $(sort $(COMMON_OBJECTS) $(PUSH_SWAP_OBJECTS) \
	$(CHECKER_OBJECTS))
OBJ_DIRS          := $(sort $(dir $(ALL_OBJECTS)))
DEPS              := $(ALL_OBJECTS:.o=.d)

.DEFAULT_GOAL := all
.DELETE_ON_ERROR:

all: $(NAME)

bonus: $(CHECKER)

$(NAME): $(COMMON_OBJECTS) $(PUSH_SWAP_OBJECTS) $(LIBFT)
	@printf "$(TAG_LD)[LD]$(RESET) Linking $(DIM)%s$(RESET)\n" "$@"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJECTS) $(PUSH_SWAP_OBJECTS) \
		$(LIBFT) $(LDLIBS) -o $@

$(CHECKER): $(COMMON_OBJECTS) $(CHECKER_OBJECTS) $(LIBFT)
	@printf "$(TAG_LD)[LD]$(RESET) Linking $(DIM)%s$(RESET)\n" "$@"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJECTS) $(CHECKER_OBJECTS) \
		$(LIBFT) $(LDLIBS) -o $@

$(LIBFT): $(LIBFT_INPUTS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

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
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:
	@rm -rf $(BUILD_DIR)
	@printf "$(TAG_CLEAN)[CLEAN]$(RESET) Removing build directory\n"
	@rm -f $(NAME) $(CHECKER)
	@printf "$(TAG_FCLEAN)[FCLEAN]$(RESET) Removing $(DIM)%s$(RESET)\n" \
		"$(NAME) and $(CHECKER)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all bonus clean fclean re
