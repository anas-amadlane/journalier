NAME	=	journalier

LIBS	=	-lxlsxio_read -lxlsxio_write -lsqlite3 `pkg-config --cflags --libs gtk+-3.0`

CFLAGS	=	-Wall -Wextra -Werror $(LIBS)

SRC		=	src/init_gui.c src/init_xlsx.c src/init_sql.c src/sql_insert.c src/tools.c src/export_xlsx.c

OBJ		=	$(SRC:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ) src/jheader.h
		@ echo "Compiling..., please wait!"
		@ mkdir -p .databases output
		@ $(MAKE) --no-print-directory -C inc/libft
		@ $(CC) $(CFLAGS) -o $(NAME) $(OBJ) inc/libft/libft.a
		@ echo "The journalier app has been successfully created!"

leak	:	$(OBJ) src/jheader.h
		@ echo "Compiling..., please wait!"
		@ mkdir -p .databases output
		@ $(MAKE) --no-print-directory -C inc/libft
		@ $(CC) -fsanitize=address -fno-omit-frame-pointer -g $(CFLAGS) -o $(NAME) $(OBJ) inc/libft/libft.a
		@ echo "The journalier app has been successfully created!"

clean	:
		@ echo "Cleaning up object files!"
		@ $(MAKE) --no-print-directory clean -C inc/libft
		@ $(RM) -f $(OBJ)

fclean	:	clean
		@ echo "Deletion of The journalier app!"
		@ $(MAKE) --no-print-directory fclean -C inc/libft
		@ $(RM) -rf .databases output
		@ $(RM) -f $(NAME)

re		:	fclean $(NAME)