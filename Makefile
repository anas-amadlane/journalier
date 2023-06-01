NAME	=	journalier

LIBS	=	-lxlsxio_read -lxlsxio_write -lsqlite3 `pkg-config --cflags --libs gtk+-3.0`

CFLAGS	=	-Wall -Wextra -Werror -DAPPNAME=10 $(LIBS)

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

win		:	$(OBJ) src/jheader.h
		mkdir -p .databases output
		x86_64-w64-mingw32-gcc -o journalier.exe $(SRC) inc/libft/ft_strncmp.c inc/libft/ft_strlen.c inc/libft/ft_strdup.c inc/libft/ft_putendl_fd.c inc/libft/ft_split.c inc/libft/ft_strlcpy.c inc/libft/ft_atoi.c inc/libft/ft_strjoin.c inc/libft/ft_strlcat.c inc/libft/ft_strtrim.c inc/libft/ft_strchr.c inc/libft/ft_substr.c inc/libft/ft_putstr_fd.c inc/libft/ft_putchar_fd.c -I/mingw64/include -I/mingw64/include/gtk-3.0 -I/mingw64/include/glib-2.0 -I/mingw64/include/pango-1.0 -I/mingw64/include/harfbuzz -I/mingw64/include/cairo -I/mingw64/include/gdk-pixbuf-2.0 -I/mingw64/include/atk-1.0 -I/mingw64/lib/glib-2.0/include -I/home/anas/clones/journalier/inc/libft -L/mingw64/lib -lgtk-3 -lglib-2.0 -lpango-1.0 -lharfbuzz -lcairo -lgdk_pixbuf-2.0 -latk-1.0 -lxlsxio_read -lxlsxio_write -lsqlite3 -mwindows -mconsole -Wall `pkg-config --cflags --libs gtk+-3.0`

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