/* bacCloneAlias.h was originally generated by the autoSql program, which also 
 * generated bacCloneAlias.c and bacCloneAlias.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2005 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef BACCLONEALIAS_H
#define BACCLONEALIAS_H

#define BACCLONEALIAS_NUM_COLS 2

struct bacCloneAlias
/* BAC clones aliases and associated STS aliases and external BAC clone names */
    {
    struct bacCloneAlias *next;  /* Next in singly linked list. */
    char *alias;	/* BAC clone alias (internal Sanger FPC name) and STS aliases */
    char *sangerName;	/* Sanger STS name */
    };

void bacCloneAliasStaticLoad(char **row, struct bacCloneAlias *ret);
/* Load a row from bacCloneAlias table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct bacCloneAlias *bacCloneAliasLoad(char **row);
/* Load a bacCloneAlias from row fetched with select * from bacCloneAlias
 * from database.  Dispose of this with bacCloneAliasFree(). */

struct bacCloneAlias *bacCloneAliasLoadAll(char *fileName);
/* Load all bacCloneAlias from whitespace-separated file.
 * Dispose of this with bacCloneAliasFreeList(). */

struct bacCloneAlias *bacCloneAliasLoadAllByChar(char *fileName, char chopper);
/* Load all bacCloneAlias from chopper separated file.
 * Dispose of this with bacCloneAliasFreeList(). */

#define bacCloneAliasLoadAllByTab(a) bacCloneAliasLoadAllByChar(a, '\t');
/* Load all bacCloneAlias from tab separated file.
 * Dispose of this with bacCloneAliasFreeList(). */

struct bacCloneAlias *bacCloneAliasCommaIn(char **pS, struct bacCloneAlias *ret);
/* Create a bacCloneAlias out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new bacCloneAlias */

void bacCloneAliasFree(struct bacCloneAlias **pEl);
/* Free a single dynamically allocated bacCloneAlias such as created
 * with bacCloneAliasLoad(). */

void bacCloneAliasFreeList(struct bacCloneAlias **pList);
/* Free a list of dynamically allocated bacCloneAlias's */

void bacCloneAliasOutput(struct bacCloneAlias *el, FILE *f, char sep, char lastSep);
/* Print out bacCloneAlias.  Separate fields with sep. Follow last field with lastSep. */

#define bacCloneAliasTabOut(el,f) bacCloneAliasOutput(el,f,'\t','\n');
/* Print out bacCloneAlias as a line in a tab-separated file. */

#define bacCloneAliasCommaOut(el,f) bacCloneAliasOutput(el,f,',',',');
/* Print out bacCloneAlias as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* BACCLONEALIAS_H */
