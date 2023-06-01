#define EXPORT_XLSX_C
#include "jheader.h"

int	export_bl(const char *xlsx_file, const char *site, const char **date) {
	int			col;
	int			ncol;
	t_exp		exp_arg;
	char		**header;
	const char	*col_value;

	ncol = extention_checker(xlsx_file);
	if (!ncol)
		return (1);
	else {
		if (ncol == -1) {
			xlsx_file = ft_strjoin(xlsx_file, ".xlsx");
			if (!xlsx_file || init_export(&exp_arg, xlsx_file, site, date))
				return (free((char *)xlsx_file), 1);
			free((char *)xlsx_file);
		}
		else if (init_export(&exp_arg, xlsx_file, site, date))
			return (1);
	}
	header = ft_split(EXP_HEAD, ',');
	if (!header)
		return (1);
	ncol = -1;
	while (header[++ncol]) {
		xlsxiowrite_add_column(exp_arg.file, header[ncol], 10);
		free(header[ncol]);
	}
	free(header);
	while (sqlite3_step(exp_arg.table) == SQLITE_ROW) {
		col = -1;
		xlsxiowrite_next_row(exp_arg.file);
		while (++col < ncol) {
			col_value = (const char *)sqlite3_column_text(exp_arg.table, col);
			xlsxiowrite_add_cell_string(exp_arg.file, col_value);
		}
	}
	sqlite3_finalize(exp_arg.table);
	sqlite3_close(exp_arg.db);
	xlsxiowrite_close(exp_arg.file);
	return (0);
}

static	int	extention_checker(const char *s) {
	int		i;
	int		r;
	char **ns;

	r = -1;
	ns = ft_split(s, '.');
	if (ns) {
		i = -1;
		while (ns[++i]);
		i = i - 1;
		if (!ft_strncmp("csv", ns[i], 3) && ft_strlen(ns[i]) == 3)
			r = CSV;
		else if (!ft_strncmp("xlsx", ns[i], 4) && ft_strlen(ns[i]) == 4)
			r = XLSX;
		else if (i)
			r = 0;
		i = -1;
		while (ns[++i])
			free(ns[i]);
		free(ns);
	}
	return (r);
}

static int	init_export(t_exp *arg, const char *xlsx_file, const char *site, const char **date) {
	char	*query;

	if (!arg)
		return (1);
	arg->db = NULL;
	if (!sqlite3_open(dbname, &arg->db)) {
		if (query_generater(&query, site, date))
			return (1);
		if (sqlite3_prepare_v2(arg->db, query, -1, &arg->table, NULL))
			return (free(query), ft_putendl_fd((char *)sqlite3_errmsg(arg->db), 2), sqlite3_close(arg->db), 1);
		else {
			free(query);
			arg->file = xlsxiowrite_open(xlsx_file, "Sheet1");
			if (!arg->file)
				return (sqlite3_close(arg->db), ft_putendl_fd("Error creating XLSX file", 2), 1);
		}
	}
	else
		return (ft_putendl_fd((char *)sqlite3_errmsg(arg->db), 2), 1);
	return (0);
}

static int	query_generater(char **query, const char *site, const char **date)
{
	size_t	len;

	if (date && query)
	{
		len = ft_strlen(site);
		if (date[0] && date[1])
			*query = formater(len + 72, EXP_QU_WD, site, date[0], date[1]);
		else if (date[0] || date[1])
		{
			if (date[0])
				*query = formater(len + 48, EXP_QU_OD, site, date[0]);
			else
				*query = formater(len + 48, EXP_QU_OD, site, date[1]);
		}
		else
			*query = formater(len + 24, EXP_QU_ND, site);
		return (0);
	}
	return (1);
}
