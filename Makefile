NAME	=	bin/journalier

WNAME	=	bin/journalier.exe

LIBS	=	-I/home/anas/clones/journalier/inc -L/home/anas/clones/journalier/lib -lxlsxio_read -lxlsxio_write -lsqlite3 `pkg-config --cflags --libs gtk+-3.0`

CFLAGS	=	-Wall -Wextra -Werror -DAPPNAME=10 $(LIBS)

SRC		=	src/init_gui.c src/init_xlsx.c src/init_sql.c src/sql_insert.c src/tools.c src/export_xlsx.c

OBJ		=	$(SRC:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
		@ echo "Compiling..., please wait!"
		@ mkdir -p .databases output
		@ $(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lft

leaks	:	$(OBJ)
		@ echo "Compiling..., please wait!"
		@ mkdir -p .databases output
		@ $(CC) -fsanitize=address -fno-omit-frame-pointer -g $(CFLAGS) -o $(NAME) $(OBJ) -lft

lwin	:	$(OBJ)
		x86_64-w64-mingw32-gcc -w -Wl,-subsystem,windows $(SRC) -I/home/anas/clones/journalier/inc -L/home/anas/clones/journalier/lib -I/mingw64/include -I/mingw64/include/gtk-3.0 -I/mingw64/include/glib-2.0 -I/mingw64/include/pango-1.0 -I/mingw64/include/harfbuzz -I/mingw64/include/cairo -I/mingw64/include/gdk-pixbuf-2.0 -I/mingw64/include/atk-1.0 -I/mingw64/lib/glib-2.0/include -L/mingw64/lib -lgtk-3 -lglib-2.0 -lpango-1.0 -lharfbuzz -lcairo -lgdk_pixbuf-2.0 -latk-1.0 -lxlsxio_read -lxlsxio_write -lsqlite3 -mwindows -mconsole -Wall `pkg-config --cflags --libs gtk+-3.0` -llwft -o $(WNAME)

wwin	: $(OBJ)
		gcc -o $(WNAME) $(SRC) -IC:/msys64/mingw64/bin/../include/gtk-3.0 -IC:/msys64/mingw64/bin/../include/pango-1.0 -IC:/msys64/mingw64/bin/../include -IC:/msys64/mingw64/bin/../include/glib-2.0 -IC:/msys64/mingw64/bin/../lib/glib-2.0/include -IC:/msys64/mingw64/bin/../include/harfbuzz -IC:/msys64/mingw64/bin/../include/freetype2 -IC:/msys64/mingw64/bin/../include/libpng16 -IC:/msys64/mingw64/bin/../include/fribidi -IC:/msys64/mingw64/bin/../include/cairo -IC:/msys64/mingw64/bin/../include/lzo -IC:/msys64/mingw64/bin/../include/pixman-1 -IC:/msys64/mingw64/bin/../include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/bin/../include/atk-1.0 -mms-bitfields -LC:/msys64/mingw64/bin/../lib -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -l"pangowin32-1.0" -l"pangocairo-1.0" -l"pango-1.0" -lharfbuzz -l"atk-1.0" -lcairo-gobject -lcairo -l"gdk_pixbuf-2.0" -l"gio-2.0" -l"gobject-2.0" -l"glib-2.0" -lintl -lxlsxio_read -lxlsxio_write -lsqlite3

clean	:
		@ echo "Cleaning up object files!"
		@ $(RM) -f $(OBJ)

fclean	:	clean
		@ echo "Deletion of The journalier app!"
		@ $(RM) -rf .databases output
		@ $(RM) -f $(NAME)
		@ $(RM) -f $(WNAME)

re		:	fclean $(NAME)

#-w -Wl,-subsystem,windows
#gcc src/init_gui.c src/init_xlsx.c src/init_sql.c src/sql_insert.c src/tools.c src/export_xlsx.c -IC:/msys64/mingw64/bin/../include/gtk-3.0 -IC:/msys64/mingw64/bin/../include/pango-1.0 -IC:/msys64/mingw64/bin/../include -IC:/msys64/mingw64/bin/../include/glib-2.0 -IC:/msys64/mingw64/bin/../lib/glib-2.0/include -IC:/msys64/mingw64/bin/../include/harfbuzz -IC:/msys64/mingw64/bin/../include/freetype2 -IC:/msys64/mingw64/bin/../include/libpng16 -IC:/msys64/mingw64/bin/../include/fribidi -IC:/msys64/mingw64/bin/../include/cairo -IC:/msys64/mingw64/bin/../include/lzo -IC:/msys64/mingw64/bin/../include/pixman-1 -IC:/msys64/mingw64/bin/../include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/bin/../include/atk-1.0 -mms-bitfields -LC:/msys64/mingw64/bin/../lib -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -l"pangowin32-1.0" -l"pangocairo-1.0" -l"pango-1.0" -lharfbuzz -l"atk-1.0" -lcairo-gobject -lcairo -l"gdk_pixbuf-2.0" -l"gio-2.0" -l"gobject-2.0" -l"glib-2.0" -lintl -lxlsxio_read -lxlsxio_write -lsqlite3 -llwft -o journalier.exe