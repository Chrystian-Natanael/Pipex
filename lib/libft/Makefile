# ! --------------------------------------------------------------------------------------------------------------------------------
# ! NAME

NAME := libft.a
.PHONY:	all clean fclean re bonus

# ! --------------------------------------------------------------------------------------------------------------------------------
# ! COLORS

GREEN = \033[32m
YELLOW = \033[33m
PURPLE = \033[35m
RED = \033[31m
WHITE = \033[37m
FCOLOR = \033[0m

# ! --------------------------------------------------------------------------------------------------------------------------------
# ! PATH

PATHSRC_LIB = source/libft
PATHSRC_GNL = source/gnl
PATHSRC_PRINTF = source/printf
PATHOBJ = obj
PATCHINLCUDE = include/

# ! --------------------------------------------------------------------------------------------------------------------------------
# ! COMMANDS

SHELL := /bin/bash
MKDIR := mkdir -p
CC := cc
AR := ar -rcs
RM := rm -rf

# ! --------------------------------------------------------------------------------------------------------------------------------
# ! FILES

SRCS_LIB :=	ft_isalpha.c \
			ft_isdigit.c \
			ft_strlen.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_putnbr_hex.c

SRCS_GNL :=	get_next_line.c \
			get_next_line_utils.c

SRCS_PRINTF :=	ft_printf.c \
				ft_hash.c \
				ft_parse.c \
				ft_plus.c \
				ft_print_build.c \
				ft_put_ptr.c \
				ft_space.c \
				ft_space_s.c \
				ft_flag_check.c

OBJS_LIB = $(patsubst %, $(PATHOBJ)/%, $(notdir $(SRCS_LIB:.c=.o)))
OBJS_GNL = $(patsubst %, $(PATHOBJ)/%, $(notdir $(SRCS_GNL:.c=.o)))
OBJS_PRINTF = $(patsubst %, $(PATHOBJ)/%, $(notdir $(SRCS_PRINTF:.c=.o)))

CFLAGS := -Wall -Wextra -Werror -g3 -Ofast

# ! --------------------------------------------------------------------------------------------------------------------------------
# ! OTHER VARIABLES

COUNT_LIB ?= 0
COUNT_GNL ?= 0
COUNT_PRINTF ?= 0

# ! --------------------------------------------------------------------------------------------------------------------------------
# ! RULES 

all: $(PATHOBJ) $(NAME)
	@sleep 0.01
	@printf "\n$(GREEN)COMPILED:$(FCOLOR)$(PURPLE) $(NAME)$(FCOLOR)\n"

$(PATHOBJ):
	@$(MKDIR) $@

$(PATHOBJ)/%.o: $(PATHSRC_LIB)/%.c 
	@$(eval COUNT_LIB=$(shell expr $(COUNT_LIB) + 1))
	@$(CC) $(CFLAGS) -I$(PATCHINLCUDE) -c $< -o $@
	@printf "Compiling $(YELLOW)LIBFT %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT_LIB) * 100 / $(words $(SRCS_LIB)))))

$(PATHOBJ)/%.o: $(PATHSRC_GNL)/%.c 
	@$(eval COUNT_GNL=$(shell expr $(COUNT_GNL) + 1))
	@$(CC) $(CFLAGS) -I$(PATCHINLCUDE) -c $< -o $@
	@printf "Compiling $(YELLOW)GNL %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT_GNL) * 100 / $(words $(SRCS_GNL)))))

$(PATHOBJ)/%.o: $(PATHSRC_PRINTF)/%.c 
	@$(eval COUNT_PRINTF=$(shell expr $(COUNT_PRINTF) + 1))
	@$(CC) $(CFLAGS) -I$(PATCHINLCUDE) -c $< -o $@
	@printf "Compiling $(YELLOW)PRINTF %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT_PRINTF) * 100 / $(words $(SRCS_PRINTF)))))

$(NAME): $(OBJS_LIB) $(OBJS_GNL) $(OBJS_PRINTF)
	@$(AR) $@ $(OBJS_LIB) $(OBJS_GNL) $(OBJS_PRINTF)
	@sleep 0.01

clean:
	@$(RM) $(PATHOBJ)
	@printf "$(RED)CLEANED FILES:$(FCOLOR)$(PURPLE) .o$(FCOLOR)\n"

fclean:	clean
	@$(RM) $(NAME)
	@printf "$(RED)CLEANED LIB:$(FCOLOR)$(PURPLE) $(NAME)$(FCOLOR)\n"

re:	fclean all
