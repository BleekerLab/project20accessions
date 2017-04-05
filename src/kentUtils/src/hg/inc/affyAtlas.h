/* affyAtlas.h was originally generated by the autoSql program, which also 
 * generated affyAtlas.c and affyAtlas.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef AFFYATLAS_H
#define AFFYATLAS_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

struct affyAtlas
/* analysis information from Affymetrix human atlas data */
    {
    struct affyAtlas *next;  /* Next in singly linked list. */
    char *annName;	/* analysis name, array name? */
    char *probeSet;	/* probe set that signal corresponds to */
    float signal;	/* signal of probeset detected */
    char detection[3];	/* not sure... */
    float pval;	/* p-value */
    char *tissue;	/* tissue sample comes from */
    };

void affyAtlasStaticLoad(char **row, struct affyAtlas *ret);
/* Load a row from affyAtlas table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct affyAtlas *affyAtlasLoad(char **row);
/* Load a affyAtlas from row fetched with select * from affyAtlas
 * from database.  Dispose of this with affyAtlasFree(). */

struct affyAtlas *affyAtlasLoadAll(char *fileName);
/* Load all affyAtlas from a tab-separated file.
 * Dispose of this with affyAtlasFreeList(). */

struct affyAtlas *affyAtlasLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all affyAtlas from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with affyAtlasFreeList(). */

void affyAtlasSaveToDb(struct sqlConnection *conn, struct affyAtlas *el, char *tableName, int updateSize);
/* Save affyAtlas as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct affyAtlas *affyAtlasCommaIn(char **pS, struct affyAtlas *ret);
/* Create a affyAtlas out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new affyAtlas */

void affyAtlasFree(struct affyAtlas **pEl);
/* Free a single dynamically allocated affyAtlas such as created
 * with affyAtlasLoad(). */

void affyAtlasFreeList(struct affyAtlas **pList);
/* Free a list of dynamically allocated affyAtlas's */

void affyAtlasOutput(struct affyAtlas *el, FILE *f, char sep, char lastSep);
/* Print out affyAtlas.  Separate fields with sep. Follow last field with lastSep. */

#define affyAtlasTabOut(el,f) affyAtlasOutput(el,f,'\t','\n');
/* Print out affyAtlas as a line in a tab-separated file. */

#define affyAtlasCommaOut(el,f) affyAtlasOutput(el,f,',',',');
/* Print out affyAtlas as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* AFFYATLAS_H */

