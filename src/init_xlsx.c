#define INIT_XLSX_C
#include "jheader.h"

int	init_xlsx(const char *file, const char *site) {
	int					rt;
	const	char		*sheetname;
	xlsxioreader		table;
	xlsxioreadersheet	sheet;

	rt = 1;
	sheetname = NULL;
	if (file && extention_checker(file) == XLSX) {
		table = xlsxioread_open(file);
		if (table) {
			sheet = xlsxioread_sheet_open(table, sheetname, XLSXIOREAD_SKIP_NONE);
			if (sheet) {
				if (xlsxioread_sheet_next_row(sheet)) {
					rt = init_insert(sheet, table_spec(sheet), site);
					return (
						xlsxioread_sheet_close(sheet),
						xlsxioread_close(table),
						rt
					);
				}
				xlsxioread_sheet_close(sheet);
			}
			xlsxioread_close(table);
		}
	}
	return (ft_putendl_fd("file load faild!", 2), rt);
}

static	int	extention_checker(const char *s) {
	int		i;
	int		r;
	char **ns;

	r = 0;
	ns = ft_split(s, '.');
	if (ns) {
		i = -1;
		while (ns[++i]);
		i = i - 1;
		if (!ft_strncmp("csv", ns[i], 3) && ft_strlen(ns[i]) == 3)
			r = CSV;
		else if (!ft_strncmp("xlsx", ns[i], 4) && ft_strlen(ns[i]) == 4)
			r = XLSX;
		i = -1;
		while (ns[++i])
			free(ns[i]);
		free(ns);
	}
	return (r);
}

static int	table_spec(xlsxioreadersheet sheet) {
	size_t	len;
	char	*header;
	char	*value;

	header = NULL;
	value = xlsxioread_sheet_next_cell(sheet);
	if (!value)
		return (0);
	while (value) {
		header = perfect_join(header, value, ",");
		if (!header)
			return (0);
		xlsxioread_free(value);
		value = xlsxioread_sheet_next_cell(sheet);
	}
	len = ft_strlen(header);
	if (!ft_strncmp(header, MAT_X, len) && len == ft_strlen(MAT_X))
		return (free(header), 1);
	else if (!ft_strncmp(header, CLT_X, len) && len == ft_strlen(CLT_X))
		return (free(header), 2);
	else if (!ft_strncmp(header, BL_X, len) && len == ft_strlen(BL_X))
		return (free(header), 3);
	else
		return (free(header), 0);
}
