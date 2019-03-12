##
## EPITECH PROJECT, 2017
## makefile
## File description:
## c
##

CC	=	gcc

CFLAGS	=	-W -Wall -Wextra -I./include/

NM_SRC		=		nm/main.c					\
					nm/core_output.c			\
					nm/core_process.c			\
					nm/symbol_sort.c			\
					nm/symbol_struct.c			\
					nm/symbol_type.c
OBJDUMP_SRC	=		objdump/main.c				\
					objdump/core_process.c		\
					objdump/section_header.c	\
					objdump/section_dump.c

NM_OBJ		=	$(NM_SRC:.c=.o)
OBJDUMP_OBJ	=	$(OBJDUMP_SRC:.c=.o)

NM	=		my_nm
OBJDUMP	=	my_objdump

all:	nm	objdump

nm: 			$(NM_OBJ)
	$(CC) $(CFLAGS) -o $(NM) $(NM_OBJ)

objdump:		$(OBJDUMP_OBJ)
	$(CC) $(CFLAGS) -o $(OBJDUMP) $(OBJDUMP_OBJ)

clean:
	rm -f $(OBJDUMP_OBJ)
	rm -f $(NM_OBJ)

fclean:	clean
	rm -f $(NM)
	rm -f $(OBJDUMP)

re:	fclean all