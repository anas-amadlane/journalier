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

win		:	$(OBJ) src/jheader.h
		mkdir -p .databases output
		x86_64-w64-mingw32-gcc -o journalier.exe src/init_gui.c src/init_xlsx.c src/init_sql.c src/sql_insert.c src/tools.c src/export_xlsx.c inc/libft/ft_strncmp.c inc/libft/ft_strlen.c inc/libft/ft_strdup.c inc/libft/ft_putendl_fd.c inc/libft/ft_split.c inc/libft/ft_strlcpy.c inc/libft/ft_atoi.c inc/libft/ft_strjoin.c inc/libft/ft_strlcat.c inc/libft/ft_strtrim.c inc/libft/ft_strchr.c inc/libft/ft_substr.c inc/libft/ft_putstr_fd.c inc/libft/ft_putchar_fd.c -IC:/msys64/mingw64/bin/../include/gtk-3.0 -IC:/msys64/mingw64/bin/../include/pango-1.0 -IC:/msys64/mingw64/bin/../include -IC:/msys64/mingw64/bin/../include/glib-2.0 -IC:/msys64/mingw64/bin/../lib/glib-2.0/include -IC:/msys64/mingw64/bin/../include/harfbuzz -IC:/msys64/mingw64/bin/../include/freetype2 -IC:/msys64/mingw64/bin/../include/libpng16 -IC:/msys64/mingw64/bin/../include/fribidi -IC:/msys64/mingw64/bin/../include/cairo -IC:/msys64/mingw64/bin/../include/lzo -IC:/msys64/mingw64/bin/../include/pixman-1 -IC:/msys64/mingw64/bin/../include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/bin/../include/atk-1.0 -mms-bitfields -LC:/msys64/mingw64/bin/../lib -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -ld -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl -lxlsxio_read -lxlsxio_write -lsqlite3
		gcc -o journalier.exe src/init_gui.c src/init_xlsx.c src/init_sql.c src/sql_insert.c src/tools.c src/export_xlsx.c src/ft_strncmp.c src/ft_strlen.c src/ft_strdup.c src/ft_putendl_fd.c src/ft_split.c src/ft_strlcpy.c src/ft_atoi.c src/ft_strjoin.c src/ft_strlcat.c src/ft_strtrim.c src/ft_strchr.c src/ft_substr.c src/ft_putstr_fd.c src/ft_putchar_fd.c -IC:/msys64/mingw64/bin/../include/gtk-3.0 -IC:/msys64/mingw64/bin/../include/pango-1.0 -IC:/msys64/mingw64/bin/../include -IC:/msys64/mingw64/bin/../include/glib-2.0 -IC:/msys64/mingw64/bin/../lib/glib-2.0/include -IC:/msys64/mingw64/bin/../include/harfbuzz -IC:/msys64/mingw64/bin/../include/freetype2 -IC:/msys64/mingw64/bin/../include/libpng16 -IC:/msys64/mingw64/bin/../include/fribidi -IC:/msys64/mingw64/bin/../include/cairo -IC:/msys64/mingw64/bin/../include/lzo -IC:/msys64/mingw64/bin/../include/pixman-1 -IC:/msys64/mingw64/bin/../include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/bin/../include/atk-1.0 -mms-bitfields -LC:/msys64/mingw64/bin/../lib -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -l"pangowin32-1.0" -l"pangocairo-1.0" -l"pango-1.0" -lharfbuzz -l"atk-1.0" -lcairo-gobject -lcairo -l"gdk_pixbuf-2.0" -l"gio-2.0" -l"gobject-2.0" -l"glib-2.0" -lintl -lxlsxio_read -lxlsxio_write -lsqlite3

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