# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 16:24:36 by lde-moul          #+#    #+#              #
#    Updated: 2019/09/17 19:45:37 by lde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

BASENAME = libft_malloc
NAME = $(BASENAME)_$(HOSTTYPE).so
LINKNAME = $(BASENAME).so

CC = clang
CFLAGS = -Wall -Wextra -Werror

SRCDIR = src
OBJDIR = obj

SRC = malloc.c\
      realloc.c\
      free.c\
      show_alloc_mem.c\
      util.c\

DEP = malloc.h\

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
SRC := $(SRC:%=$(SRCDIR)/%)
DEP := $(DEP:%=$(SRCDIR)/%)

LIBFT_DIR = libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)/includes


all: $(LINKNAME)

clean:
	@make -C $(LIBFT_DIR) fclean
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINKNAME)

re: fclean all

$(NAME): $(LIBFT_NAME) $(OBJDIR) $(OBJ)
	@$(CC) -shared $(CFLAGS) -o $@ $(OBJ) $(LIBFT_NAME)

$(LINKNAME): $(NAME)
	@/bin/ln -sf $(NAME) $(LINKNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEP)
	@$(CC) -fPIC $(CFLAGS) -o $@ -c $< -I$(LIBFT_INC)

$(OBJDIR):
	@/bin/mkdir $(OBJDIR)

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

.PHONY: all clean fclean re
