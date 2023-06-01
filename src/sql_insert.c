#define SQL_INSERT_C
#include <jheader.h>

int	init_insert(xlsxioreadersheet sheet, int table, const char *site)
{
	t_table	protype;

	//printf("%s\n", wd);
	protype.db = init_db(dbname, table, site);
	if (!protype.db)
		return (ft_putendl_fd("Database creation failed", 2), 1);
	query_init(table, site, &protype);
	if (insert_query(sheet, &protype, table))
		return (1);
	sqlite3_close(protype.db);
	if (table == BL)
		free(protype.query);
	return (0);
}

static int	query_init(int table, const char *site, t_table *protype)
{
	size_t	len;

	if (protype && table == MAT)
	{
		protype->col = 8;
		protype->query = MAT_QUERY;
	}
	else if (protype && table == CLT)
	{
		protype->col = 4;
		protype->query = CLT_QUERY;
	}
	else if (protype && table == BL)
	{
		protype->col = 23;
		len = ft_strlen(BL_QUERY) - 2 + ft_strlen(site);
		protype->query = formater(len, BL_QUERY, site);
		if (!protype->query)
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	insert_query(xlsxioreadersheet sheet, t_table *protype, int table)
{
	int		i;
	int		j;
	char	*value;
	char	*query;

	i = 0;
	query = NULL;
	query_hold(protype->query, &query);
	while (xlsxioread_sheet_next_row(sheet))
	{
		j = 0;
		value = xlsxioread_sheet_next_cell(sheet);
		while (value)
		{
			if (!j)
			{
				if (!i)
					query_hold("(\'", &query);
				else
					query_hold(",(\'", &query);
			}
			else
				query_hold("\',\'", &query);
			if (j == 2 && table == BL)
				query_hold(convert_date(value), &query);
			else
				query_hold(value, &query);
			xlsxioread_free(value);
			value = xlsxioread_sheet_next_cell(sheet);
			j++;
		}
		while (protype->col > j++)
			query_hold("\',\'", &query);
		if (++i == 100)
		{
			i = 0;
			query_hold("\');", &query);
			if (query_exec(&query, protype))
				return (1);
			query_hold(protype->query, &query);
		}
		else
			query_hold("\')", &query);
	}
	if (i)
	{
		query_hold(";", &query);
		if (query_exec(&query, protype))
			return (1);
	}
	return (0);
}

static int	query_hold(char *s, char **query)
{
	int			i;
	int			l;
	static int	len;
	char		*tmp;

	if (*query && s)
	{
		l = ft_strlen(s);
		if (len + l < MAX_ALLOC)
		{
			i = -1;
			while (s[++i])
				(*query)[len++] = s[i];
			(*query)[len] = '\0';
		}
		else
		{
			len += l;
			tmp = *query;
			*query = (char *)malloc(sizeof(char) * (len + 1));
			if (!(*query))
				return (1);
			i = -1;
			while (tmp[++i])
				(*query)[i] = tmp[i];
			l = -1;
			while (s[++l])
				(*query)[i++] = s[l];
			(*query)[i] = '\0';
			free(tmp);
		}
	}
	else if (s)
	{
		len = ft_strlen(s);
		*query = (char *)malloc(sizeof(char) * MAX_ALLOC);
		if (!(*query))
			return (1);
		i = -1;
		while (s[++i])
			(*query)[i] = s[i];
		(*query)[i] = '\0';
	}
	else
		return (1);
	return (0);
}

static int	query_exec(char **query, t_table *protype)
{
	char	*errorMsg;

	errorMsg = NULL;
	if (sqlite3_exec(protype->db, *query, NULL, 0, &errorMsg))
		return(ft_putendl_fd(errorMsg, 2), 1);
	free(*query);
	*query = NULL;
	return (0);
}
