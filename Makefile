#! ******************************************************************************#
#                                   NAME                                         #
#! ******************************************************************************#

NAME = pipex
NAME_BONUS = pipex_bonus
.DEFAULT_GOAL := all
.PHONY: all clean fclean re bonus
.SILENT:

#! ******************************************************************************#
#                                   COLORS                                       #
#! ******************************************************************************#

GREEN = \033[32m
YELLOW = \033[33m
PURPLE = \033[35m
RED = \033[31m
WHITE = \033[37m
RESET = \033[0m

#! ******************************************************************************#
#                                   PATH                                         #
#! ******************************************************************************#

SRCS_PATH = ./src/
INCS_PATH = ./includes/ $(LIBFT_DIR)/include
BUILD_DIR := ./build/
LIBFT_DIR := ./lib/libft/

#! ******************************************************************************#
#                                   FILES                                        #
#! ******************************************************************************#

SRCS =	$(addprefix $(SRCS_PATH),\
		main.c \
		utils.c)

SRCS_BONUS =	$(addprefix $(SRCS_PATH),\
				main_bonus.c \
				utils_bonus.c)

LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
LIBS := $(LIBFT_DIR)libft.a
OBJS = $(SRCS:%.c=$(BUILD_DIR)%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(BUILD_DIR)%.o)
DEPS = $(OBJS:.o=.d)

#! ******************************************************************************#
#                                   DEFINE                                       #
#! ******************************************************************************#

ifdef WITH_BONUS
	OBJS := $(OBJS_BONUS)
	NAME := $(NAME_BONUS)
endif

#! ******************************************************************************#
#                                    COMMANDS                                    #
#! ******************************************************************************#

MKDIR := mkdir -p
RM := rm -rf
SLEEP = sleep 0.1
CC = cc

#! ******************************************************************************#
#                                 FLAGS E COMP                                   #
#! ******************************************************************************#

CFLAGS = -Wall -Wextra -Werror -g3
DFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDLIBS = -lft -ldl -lglfw -pthread
LDFLAGS = $(addprefix -L,$(dir $(LIBS)))
CPPFLAGS = $(addprefix -I,$(INCS_PATH)) -MMD -MP
COMP_OBJ = $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
COMP_EXE = $(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

#! ******************************************************************************#
#                                  FUNCTIONS                                     #
#! ******************************************************************************#

define create_dir
	$(MKDIR) $(dir $@)
endef

define bonus
	$(MAKE) WITH_BONUS=TRUE
endef

define comp_objs
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	$(COMP_OBJ)
	$(SLEEP)
	printf "Compiling$(YELLOW) PIPEX %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT) * 100 / $(words $(SRCS)))))
	@if [ $(COUNT) -eq $(words $(SRCS)) ]; then \
		printf "\n"; \
	fi
endef

define comp_libft
	printf "$(YELLOW)Building libft files\n$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)
endef

define comp_exe
	$(COMP_EXE)
	printf "$(GREEN)PIPEX ->$(RESET)$(PURPLE) READY\n$(RESET)"
endef

#! ******************************************************************************#
#                                   TARGETS                                      #
#! ******************************************************************************#

all: $(LIBFT) $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	$(call comp_objs)

$(NAME): $(OBJS)
	$(call comp_exe)

$(LIBFT):
	$(call comp_libft)
	printf "\n"
	printf "$(YELLOW)Building Pipex files\n$(RESET)"

clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

bonus:
	$(call bonus)

re: fclean all

-include $(DEPS)
