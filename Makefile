# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-moul <lde-moul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/14 16:24:36 by lde-moul          #+#    #+#              #
#    Updated: 2021/11/29 16:25:57 by lde-moul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

BASENAME = libft_malloc
NAME = $(BASENAME)_$(HOSTTYPE).so
LINKNAME = $(BASENAME).so

CFLAGS = -Wall -Wextra -Werror

SRCDIR = src
OBJDIR = obj

SRC = malloc.c\
      realloc.c\
      calloc.c\
      free.c\
      show_alloc_mem.c\
      find_free_space.c\
      zone.c\
      align.c\
      util.c\

DEP = malloc.h\

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
SRC := $(SRC:%=$(SRCDIR)/%)
DEP := $(DEP:%=$(SRCDIR)/%)


all: $(LINKNAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LINKNAME)

re: fclean all

$(NAME): $(OBJDIR) $(OBJ)
	@$(CC) -shared $(CFLAGS) -o $@ $(OBJ)

$(LINKNAME): $(NAME)
	@/bin/ln -sf $(NAME) $(LINKNAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEP)
	@$(CC) -fPIC $(CFLAGS) -o $@ -c $<

$(OBJDIR):
	@/bin/mkdir $(OBJDIR)

.PHONY: all clean fclean re
