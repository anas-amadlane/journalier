#ifndef JHEADER_H
# define JHEADER_H
# include "../inc/libft/libft.h"
# include <stdio.h>
# include <sqlite3.h>
# include <gtk/gtk.h>
# include <xlsxio_read.h>
# include <xlsxio_write.h>

# define DB_NAME ".databases/journalier.db"
# define MAT 1
# define CLT 2
# define BL 3
# define CSV 4
# define XLSX 5

# ifdef EXPORT_XLSX_C
#  define EXP_QU_ND "SELECT * FROM BLC_VIEW_%s;"
#  define EXP_QU_WD "SELECT * FROM BLC_VIEW_%s WHERE DATE>='%s' AND DATE<='%s';"
#  define EXP_QU_OD "SELECT * FROM BLC_VIEW_%s WHERE DATE='%s';"
#  define EXP_HEAD "CLIENT,SECTEUR,DATE,NUM,TYPE,QTE,PRIX_VENTE,PRIX_GROS,PRODUIT,CODE_PHAR,CODE_PROD,CODE_LAB,LAB,ETAT,REMISE,FAMILLE,OPER,TIREUR,RAMASSEUR,LIVREUR,NUM_BORD,SACHET,COLIS,Qté corrigée,\% TVA,\% Remise,Remise TTC,C.A TTC,C.A HT,Mnt HT PNG, C.A HT Brut,Marge Brut,\% Marge,Type Clt,Nom Famille, Famille marge"

typedef struct		s_exp
{
	sqlite3			*db;
	sqlite3_stmt	*table;
	xlsxiowriter	file;
}					t_exp;

int			export_bl(const char *xlsx_file, const char *site, const char **date);
static int	extention_checker(const char *s);
static int	init_export(t_exp *arg, const char *xlsx_file, const char *site, const char **date);
static int	query_generater(char **query, const char *site, const char **date);
# endif

# ifdef INIT_SQL_C
#  define QU_MAT "CREATE TABLE IF NOT EXISTS MAT (Code_Famille VARCHAR, Désignation_Famille VARCHAR, Marge DECIMAL, Famille_Marge VARCHAR, CODE_MARGE INT, TVA DECIMAL, FAMILLE_GROUPEE_1 VARCHAR, FAMILLE_GROUPEE_2 VARCHAR);"
#  define MAT_SP "CREATE UNIQUE INDEX IF NOT EXISTS MAT_Code_Famille ON MAT ( Code_Famille );"
#  define QU_CLT "CREATE TABLE IF NOT EXISTS CLT (Site VARCHAR,CODE_Client_Site INT,Nom_CLIENT_Site VARCHAR, Type_Clt_Site VARCHAR);"
#  define CLT_SP "CREATE UNIQUE INDEX IF NOT EXISTS CLT_Site_CODE_Client_Site ON CLT ( Site,CODE_Client_Site );"
#  define QU_BL "CREATE TABLE IF NOT EXISTS BL_%s (CLIENT VARCHAR, SECTEUR UNSIGNED INT, DATE DATE, NUM UNSIGNED INT, TYPE VARCHAR, QTE UNSIGNED INT, PRIX_VENTE DECIMAL, PRIX_GROS DECIMAL, PRODUIT VARCHAR, CODE_PHAR UNSIGNED INT, CODE_PROD UNSIGNED INT, CODE_LAB UNSIGNED INT, LAB VARCHAR, ETAT VARCHAR, REMISE INT, FAMILLE VARCHAR, OPER UNSIGNED INT, TIREUR UNSIGNED INT, RAMASSEUR UNSIGNED INT, LIVREUR UNSIGNED INT, NUM_BORD UNSIGNED INT, SACHET INT, COLIS INT);"
#  define BL_SP "CREATE UNIQUE INDEX IF NOT EXISTS BL_%s_DATE_NUM ON BL_%s ( DATE, NUM, CODE_PHAR, CODE_PROD );"
#  define BLC "CREATE VIEW IF NOT EXISTS BLC_VIEW_%s AS SELECT t1.*, (SELECT CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END FROM BL_%s) AS QTE_CORR, (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille) AS TVA, (SELECT CASE WHEN TYPE = 'MR' THEN REMISE/100 ELSE 0 END FROM BL_%s) AS REMISE, (SELECT CASE WHEN TYPE = 'MR' THEN ((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 - (REMISE/100))) - (PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) ELSE 0 END FROM BL_%s) AS REMISE_TTC, (SELECT PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END) FROM BL_%s) AS CA_TTC, (SELECT (PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille)) FROM BL_%s) AS CA_HT, (SELECT (PRIX_GROS * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille)) FROM BL_%s) AS MNT_HT, (SELECT ((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille))) + (CASE WHEN TYPE = 'MR' THEN ((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 - (REMISE/100))) - (PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) ELSE 0 END) FROM BL_%s) AS CA_BRUT, (SELECT (((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille))) + (CASE WHEN TYPE = 'MR' THEN ((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 - (REMISE/100))) - (PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) ELSE 0 END)) - ((PRIX_GROS * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille))) FROM BL_%s) AS MARGE_BRUT, (SELECT ((((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille))) + (CASE WHEN TYPE = 'MR' THEN ((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 - (REMISE/100))) - (PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) ELSE 0 END)) - ((PRIX_GROS * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille)))) / (((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 + (SELECT t2.TVA FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille))) + (CASE WHEN TYPE = 'MR' THEN ((PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) / (1 - (REMISE/100))) - (PRIX_VENTE * (CASE WHEN TYPE = 'avo' THEN -QTE ELSE QTE END)) ELSE 0 END)) FROM BL_%s) AS MARGE, (SELECT t2.Type_Clt_Site FROM BL_%s t1 JOIN CLT t2 ON t1.CODE_PHAR = t2.CODE_Client_Site AND t2.Site = '%s') AS TYPE_CLT, (SELECT t2.Désignation_Famille FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille) AS NOM_FAM, (SELECT t2.Famille_Marge FROM BL_%s t1 JOIN MAT t2 ON t1.FAMILLE = t2.Code_Famille) AS FAM_MARGE FROM BL_%s t1;"

static int	bl_case(sqlite3 *db, const char *site);
static int	init_exec(sqlite3 *db, const char *q1, const char *q2);
static int	blc_view(sqlite3 *db, const char *site);
# endif

# ifdef INIT_XLSX_C
#  define CLT_X "Site,CODE_Client Site,Nom CLIENT Site,Type Clt Site"
#  define MAT_X "Code Famille,Désignation Famille,Marge,Famille Marge,CODE MARGE,% TVA,FAMILLE GROUPEE 1,FAMILLE GROUPEE 2"
#  define BL_X "CLIENT,SECTEUR,DATE,NUM,TYPE,QTE,PRIX_VENTE,PRIX_GROS,PRODUIT,CODE_PHAR,CODE_PROD,CODE_LAB,LAB,ETAT,REMISE,FAMILLE,OPER,TIREUR,RAMASSEUR,LIVREUR,NUM_BORD,SACHET,COLIS"

int			init_insert(xlsxioreadersheet sheet, int table, const char *site);
int			table_filler(xlsxioreadersheet sheet, int table, const char *site);
static int	table_spec(xlsxioreadersheet sheet);
static int	extention_checker(const char *s);
# endif

# ifdef SQL_INSERT_C
#  define MAX_ALLOC 30000
#  define CLT_QUERY "INSERT OR REPLACE INTO CLT VALUES"
#  define MAT_QUERY "INSERT OR REPLACE INTO MAT VALUES"
#  define BL_QUERY "INSERT OR REPLACE INTO BL_%s VALUES"

typedef struct s_table {
	int		col;
	char	*query;
	sqlite3	*db;
} t_table;

sqlite3		*init_db(char *dbName, int table, const char *site);
static int	query_init(int table, const char *site, t_table *protype);
static int	insert_query(xlsxioreadersheet sheet, t_table *protype, int table);
static int	query_exec(char **query, t_table *protype);
static int	query_hold(char *s, char **query);
# endif

# ifdef INIT_GUI_C
int					init_xlsx(const char *file, const char *site);
int					export_bl(const char *xlsx_file, const char *site, const char **date);
static GtkWidget	*init_box(GtkWidget *window);
static GtkWidget	*load_logo(void);
static GtkWidget	*copyright(void);
static GtkWidget	*init_combo_box(void);
static void			on_combo_box_changed(GtkComboBoxText *combo_box);
static GtkWidget	*import_button(GtkWidget *window);
static void			on_import_button_clicked(GtkButton *button, gpointer user_data);
static gpointer		process_file_async(gpointer filename);
static gboolean		destroy_dialog(gpointer dialog);
static GtkWidget	*export_button(GtkWidget *window);
static void			on_export_button_clicked(GtkButton *button, gpointer user_data);
static int			show_export_popup(GtkWidget *parent_window, char **path);
static void			on_select_path_button_clicked(GtkButton *button, gpointer user_data);
static void			on_scalendar_day_selected(GtkCalendar *calendar, gpointer user_data);
static void			on_ecalendar_day_selected(GtkCalendar *calendar, gpointer user_data);
# endif

char    *perfect_join(char *s1, char *s2, char *sep);
char	*formater(size_t len, char *form, ...);
char	*convert_date(char *s);
#endif