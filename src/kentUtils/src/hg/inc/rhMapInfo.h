/* rhMapInfo.h was originally generated by the autoSql program, which also 
 * generated rhMapInfo.c and rhMapInfo.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef RHMAPINFO_H
#define RHMAPINFO_H

#define RHMAPINFO_NUM_COLS 10

struct rhMapInfo
/* Radiation Hybrid map information */
    {
    struct rhMapInfo *next;  /* Next in singly linked list. */
    char *name;	/* Name of Radiation Hybrid (RH) map marker */
    char *zfinId;	/* ZFIN ID for the marker */
    char *linkageGp;	/* Linkage group to which the marker was mapped */
    unsigned position;	/* Position number in RH map for this linkage group */
    unsigned distance;	/* Distance from the top of linkage group (cR) */
    char *markerType;	/* Type of marker */
    char *source;	/* Source of marker */
    char *mapSite;	/* Institution that mapped the marker */
    char *leftPrimer;	/* Forward primer sequence */
    char *rightPrimer;	/* Reverse primer sequence */
    };

void rhMapInfoStaticLoad(char **row, struct rhMapInfo *ret);
/* Load a row from rhMapInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct rhMapInfo *rhMapInfoLoad(char **row);
/* Load a rhMapInfo from row fetched with select * from rhMapInfo
 * from database.  Dispose of this with rhMapInfoFree(). */

struct rhMapInfo *rhMapInfoLoadAll(char *fileName);
/* Load all rhMapInfo from whitespace-separated file.
 * Dispose of this with rhMapInfoFreeList(). */

struct rhMapInfo *rhMapInfoLoadAllByChar(char *fileName, char chopper);
/* Load all rhMapInfo from chopper separated file.
 * Dispose of this with rhMapInfoFreeList(). */

#define rhMapInfoLoadAllByTab(a) rhMapInfoLoadAllByChar(a, '\t');
/* Load all rhMapInfo from tab separated file.
 * Dispose of this with rhMapInfoFreeList(). */

struct rhMapInfo *rhMapInfoCommaIn(char **pS, struct rhMapInfo *ret);
/* Create a rhMapInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rhMapInfo */

void rhMapInfoFree(struct rhMapInfo **pEl);
/* Free a single dynamically allocated rhMapInfo such as created
 * with rhMapInfoLoad(). */

void rhMapInfoFreeList(struct rhMapInfo **pList);
/* Free a list of dynamically allocated rhMapInfo's */

void rhMapInfoOutput(struct rhMapInfo *el, FILE *f, char sep, char lastSep);
/* Print out rhMapInfo.  Separate fields with sep. Follow last field with lastSep. */

#define rhMapInfoTabOut(el,f) rhMapInfoOutput(el,f,'\t','\n');
/* Print out rhMapInfo as a line in a tab-separated file. */

#define rhMapInfoCommaOut(el,f) rhMapInfoOutput(el,f,',',',');
/* Print out rhMapInfo as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* RHMAPINFO_H */

