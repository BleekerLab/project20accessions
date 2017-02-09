/* jaxQTL.h was originally generated by the autoSql program, which also 
 * generated jaxQTL.c and jaxQTL.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef JAXQTL_H
#define JAXQTL_H

struct jaxQTL
/* Quantitative Trait Loci from Jackson Lab / Mouse Genome Informatics */
    {
    struct jaxQTL *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome or FPC contig */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    unsigned score;	/* Score from 0-1000 (bed6 compat.) */
    char strand[2];	/* + or - (bed6 compat.) */
    char *marker;	/* MIT SSLP Marker w/highest correlation */
    char *mgiID;	/* MGI ID */
    char *description;	/* MGI description */
    float cMscore;	/* cM position of marker associated with peak LOD score */
    };

void jaxQTLStaticLoad(char **row, struct jaxQTL *ret);
/* Load a row from jaxQTL table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct jaxQTL *jaxQTLLoad(char **row);
/* Load a jaxQTL from row fetched with select * from jaxQTL
 * from database.  Dispose of this with jaxQTLFree(). */

struct jaxQTL *jaxQTLLoadAll(char *fileName);
/* Load all jaxQTL from a tab-separated file.
 * Dispose of this with jaxQTLFreeList(). */

struct jaxQTL *jaxQTLLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all jaxQTL from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with jaxQTLFreeList(). */

struct jaxQTL *jaxQTLCommaIn(char **pS, struct jaxQTL *ret);
/* Create a jaxQTL out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new jaxQTL */

void jaxQTLFree(struct jaxQTL **pEl);
/* Free a single dynamically allocated jaxQTL such as created
 * with jaxQTLLoad(). */

void jaxQTLFreeList(struct jaxQTL **pList);
/* Free a list of dynamically allocated jaxQTL's */

void jaxQTLOutput(struct jaxQTL *el, FILE *f, char sep, char lastSep);
/* Print out jaxQTL.  Separate fields with sep. Follow last field with lastSep. */

#define jaxQTLTabOut(el,f) jaxQTLOutput(el,f,'\t','\n');
/* Print out jaxQTL as a line in a tab-separated file. */

#define jaxQTLCommaOut(el,f) jaxQTLOutput(el,f,',',',');
/* Print out jaxQTL as a comma separated list including final comma. */

#endif /* JAXQTL_H */
