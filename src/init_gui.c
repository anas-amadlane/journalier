#define INIT_GUI_C
#include <jheader.h>

const char			*wd;
const char			*dbname;
static char			*site;
static char			*date[2];
static GtkWidget	*status_label_p;
static GtkWidget	*status_label_x;

int main(int ac, char **av) {
	GtkWidget	*window;

	wd = ft_substr(av[0], 0, ft_strlen(av[0]) - APPNAME);
	if (APPNAME == 14)
		dbname = ft_strjoin(getenv("APPDATA"), "\\journalier\\journalier.db");
	else
		dbname = ft_strjoin(wd, ".databases/journalier.db");
	if (!wd || !dbname)
		return (1);
	gtk_init(&ac, &av);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Detail Journalier");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_add(GTK_CONTAINER(window), init_box(window));
	gtk_widget_show_all(window);
	gtk_main();
	return (free((char *)wd), free((char *)dbname), 0);
}

static GtkWidget *init_box(GtkWidget *window) {
	GtkWidget *grid;
	GtkWidget *vbox;

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_box_pack_start(GTK_BOX(vbox), load_logo(window), FALSE, FALSE, 20);
	gtk_box_pack_start(GTK_BOX(vbox), init_combo_box(), FALSE, FALSE, 0);

	grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

	status_label_p = gtk_label_new("Status: Idle");
	gtk_grid_attach(GTK_GRID(grid), import_button(window), 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), status_label_p, 0, 1, 1, 1);

	status_label_x = gtk_label_new("Status: Idle");
	gtk_grid_attach(GTK_GRID(grid), export_button(window), 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), status_label_x, 1, 1, 1, 1);

	gtk_box_pack_end(GTK_BOX(vbox), copyright(), FALSE, FALSE, 0);
	return vbox;
}

static GtkWidget	*load_logo(GtkWidget *window) {
	gint		new_width;
	gint		new_height;
	GList		*list;
	GtkWidget	*logo_image;
	GdkPixbuf	*logo_pixbuf;
	GdkPixbuf	*resized_logo_pixbuf;
	const char	*path;

	path = ft_strjoin(wd, "data/logo/srm.png");
	if (!path)
		return (NULL);
	logo_pixbuf = gdk_pixbuf_new_from_file(path, NULL);
	if (!logo_pixbuf)
		return (NULL);
	new_width = 150;
	new_height = (gdk_pixbuf_get_width(logo_pixbuf) * new_width) / gdk_pixbuf_get_height(logo_pixbuf);
	resized_logo_pixbuf = gdk_pixbuf_scale_simple(logo_pixbuf, new_width, new_height, GDK_INTERP_BILINEAR);
	if (!resized_logo_pixbuf)
		return (NULL);
    list = g_list_append(NULL, resized_logo_pixbuf);
    gtk_window_set_icon_list(GTK_WINDOW(window), list);
    g_list_free(list);
	logo_image = gtk_image_new_from_pixbuf(resized_logo_pixbuf);
	g_object_unref(logo_pixbuf);
	g_object_unref(resized_logo_pixbuf);
	return (free((char *)path), logo_image);
}

static GtkWidget	*copyright(void) {
	GtkWidget	*copyright_label;

	copyright_label = NULL;
	copyright_label = gtk_label_new("© 2023 SOREMED");
	gtk_widget_set_halign(GTK_WIDGET(copyright_label), GTK_ALIGN_END);
	gtk_widget_set_valign(GTK_WIDGET(copyright_label), GTK_ALIGN_END);
	return (copyright_label);
}

static GtkWidget	*init_combo_box(void) {
	GtkWidget	*combo_box;

	combo_box = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Select Site");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "SOREMED");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "CPRE");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "GPM");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "GDIS");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "LODIMED");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "COPHADIS");
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);
	g_signal_connect(combo_box, "changed", G_CALLBACK(on_combo_box_changed), NULL);
	return (combo_box);
}

static void	on_combo_box_changed(GtkComboBoxText *combo_box) {
	if (site)
		g_free((gpointer)site);
	site = gtk_combo_box_text_get_active_text(combo_box);
	g_print("Selected item: %s\n", site);
	if (ft_strncmp(gtk_label_get_text(GTK_LABEL(status_label_p)), "Status: Please wait...", 22))
		gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Idle");
	if (ft_strncmp(gtk_label_get_text(GTK_LABEL(status_label_x)), "Status: Please wait...", 22))
		gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Idle");
}

static GtkWidget    *import_button(GtkWidget *window) {
	GtkWidget	*import_button;

	import_button = NULL;
	import_button = gtk_button_new_with_label("Import");
	g_signal_connect(import_button, "clicked",
		G_CALLBACK(on_import_button_clicked), window);
	gtk_widget_set_size_request(import_button, 200, 80);
	gtk_widget_set_halign(import_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(import_button, GTK_ALIGN_CENTER);
	return (import_button);
}

static void	on_import_button_clicked(GtkButton *button, gpointer user_data) {
	char		*filename;
	GtkWidget	*dialog;
	GThread		*thread;

	(void)button;
	if (!ft_strncmp(gtk_label_get_text(GTK_LABEL(status_label_p)), "Status: Please wait...", 22))
		return ;
	if (ft_strncmp(gtk_label_get_text(GTK_LABEL(status_label_x)), "Status: Please wait...", 22))
		gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Idle");
	gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Idle");
	if (site && ft_strncmp(site, "Select Site", 11)) {
		dialog = gtk_file_chooser_dialog_new("Select File",
			GTK_WINDOW(user_data), GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel",
			GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
		if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
			filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
			thread = g_thread_new(NULL, process_file_async, (gpointer)filename);
			g_thread_unref(thread);
			g_timeout_add(100, destroy_dialog, dialog);
		}
		else
			gtk_widget_destroy(dialog);
	}
	else
		gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Select site");
}

static gboolean	destroy_dialog(gpointer dialog) {
	gtk_widget_destroy(GTK_WIDGET(dialog));
	return FALSE;
}

static gpointer	process_file_async(gpointer filename) {
	gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Please wait...");
	if (init_xlsx((char *)filename, site))
		gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Failed!");
	else
		gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Done");
	g_free(filename);
	return NULL;
}

static GtkWidget	*export_button(GtkWidget *window) {
	GtkWidget	*export_button;

	export_button = NULL;
	export_button = gtk_button_new_with_label("Export");
	g_signal_connect(export_button, "clicked",
		G_CALLBACK(on_export_button_clicked), window);
	gtk_widget_set_size_request(export_button, 200, 80);
	gtk_widget_set_halign(export_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(export_button, GTK_ALIGN_CENTER);
	return (export_button);
}

static void	on_export_button_clicked(GtkButton *button, gpointer user_data) {
	char	*path;

	(void)button;
	if (!ft_strncmp(gtk_label_get_text(GTK_LABEL(status_label_x)), "Status: Please wait...", 22))
		return ;
	if (ft_strncmp(gtk_label_get_text(GTK_LABEL(status_label_p)), "Status: Please wait...", 22))
		gtk_label_set_text(GTK_LABEL(status_label_p), "Status: Idle");
	gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Idle");
	if (site && ft_strncmp(site, "Select Site", 11)) {
		date[0] = NULL;
		date[1] = NULL;
		path = formater(15 + ft_strlen(site), "output/BL_%s.xlsx", site);
		if (!show_export_popup(GTK_WIDGET(user_data), &path)) {
			gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Please wait...");
			if (export_bl(path, site, (const char **)date))
				gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Failed!");
			else
				gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Done");
			free(date[0]);
			free(date[1]);
		}
		free(path);
	}
	else
		gtk_label_set_text(GTK_LABEL(status_label_x), "Status: Select site");
}

static int	show_export_popup(GtkWidget *parent_window, char **path) {
	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *entry;
	GtkWidget *button;
	GtkWidget *start_label;
	GtkWidget *end_label;
	GtkWidget *start_calendar;
	GtkWidget *end_calendar;

	dialog = gtk_dialog_new_with_buttons("Export", GTK_WINDOW(parent_window),
		GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "_Cancel",
		GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
	grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
	entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), *path);
	button = gtk_button_new_with_label("Select Path");
	start_label = gtk_label_new("Start Date:");
	end_label = gtk_label_new("End Date:");
	start_calendar = gtk_calendar_new();
	end_calendar = gtk_calendar_new();
	gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), start_label, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), start_calendar, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), end_label, 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), end_calendar, 2, 2, 1, 1);
	gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), grid);
	g_signal_connect(button, "clicked", G_CALLBACK(on_select_path_button_clicked), entry);
	g_signal_connect(start_calendar, "day-selected", G_CALLBACK(on_scalendar_day_selected), start_label);
	g_signal_connect(end_calendar, "day-selected", G_CALLBACK(on_ecalendar_day_selected), end_label);
	gtk_widget_show_all(dialog);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		free((*path));
		*path = ft_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
		return (gtk_widget_destroy(dialog), 0);
	}
	else
		return (gtk_widget_destroy(dialog), 1);
}

static void	on_select_path_button_clicked(GtkButton *button, gpointer user_data) {
	GtkWidget *dialog;
	char *filename;

	dialog = gtk_file_chooser_dialog_new("Select Destination",
		GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))), GTK_FILE_CHOOSER_ACTION_SAVE,
		"_Cancel", GTK_RESPONSE_CANCEL, "_Save", GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gtk_entry_set_text(GTK_ENTRY(GTK_WIDGET(user_data)), filename);
		free(filename);
	}
	gtk_widget_destroy(dialog);
}

static void	on_scalendar_day_selected(GtkCalendar *calendar, gpointer user_data) {
	GtkWidget		*label;
	char			date_str[23];
	unsigned int	year, month, day;

	label = GTK_WIDGET(user_data);
	gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
	date[0] = (char *)malloc(sizeof(char) * 11);
	if (date[0])
		sprintf((date[0]), "%04d-%02d-%02d",year, month + 1, day);
	sprintf(date_str, "Start Date: %02d/%02d/%04d", day, month + 1, year);
	gtk_label_set_text(GTK_LABEL(label), date_str);
}

static void	on_ecalendar_day_selected(GtkCalendar *calendar, gpointer user_data) {
	GtkWidget		*label;
	char			date_str[21];
	unsigned int	year, month, day;

	label = GTK_WIDGET(user_data);
	gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
	date[1] = (char *)malloc(sizeof(char) * 11);
	if (date[1])
		sprintf((date[1]), "%04d-%02d-%02d",year, month + 1, day);
	sprintf(date_str, "End Date: %02d/%02d/%04d", day, month + 1, year);
	gtk_label_set_text(GTK_LABEL(label), date_str);
}
