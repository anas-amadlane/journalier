#define INIT_SQL_C
#include "jheader.h"

sqlite3	*init_db(char *dbName, int table, const char *site)
{
	sqlite3	*db;

    db = NULL;
	if (!sqlite3_open(dbName, &db))
	{
		if ((table == MAT && init_exec(db, QU_MAT, MAT_SP))
			|| (table == CLT && init_exec(db, QU_CLT, CLT_SP))
			|| (table == BL && bl_case(db, site)))
			return (db);
		else
			return (
				sqlite3_close(db),
				ft_putendl_fd("please select a valid table", 1),
				NULL
			);
	}
	return (NULL);
}

static int	bl_case(sqlite3 *db, const char *site) {
	size_t	len[2];
	char	*query[2];

	len[0] = ft_strlen(QU_BL) - 2 + ft_strlen(site);
	len[1] = ft_strlen(BL_SP) - 4 + (ft_strlen(site) * 2);
	query[0] = formater(len[0], QU_BL, site);
	query[1] = formater(len[1], BL_SP, site, site);
	if (!query[0] || !query[1])
		return (0);
	if (init_exec(db, QU_MAT, MAT_SP)
		&& init_exec(db, QU_CLT, CLT_SP)
		&& init_exec(db, query[0], query[1]))
		return (free(query[0]), free(query[1]), blc_view(db, site));
	return(free(query[0]), free(query[1]), 0);
}

static int	init_exec(sqlite3 *db, const char *q1, const char *q2) {
	char	*err;

	err = NULL;
	if (sqlite3_exec(db, q1, NULL, 0, &err) || sqlite3_exec(db, q2, NULL, 0, &err))
		return (ft_putendl_fd(err, 2), 0);
	return (ft_putendl_fd("Database created successfully", 1), 1);
}

static int	blc_view(sqlite3 *db, const char *site)
{
	size_t		len;
	char	*query;
	char	*errorMsg;

	len = ft_strlen(BLC) - 46 + (ft_strlen(site) * 23);
	query = formater(len, BLC, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site, site);
	if (!query)
		return (0);
	errorMsg = NULL;
	if (sqlite3_exec(db, query, NULL, 0, &errorMsg))
		return(ft_putendl_fd(errorMsg, 2), 0);
	return(free(query), 1);
}
