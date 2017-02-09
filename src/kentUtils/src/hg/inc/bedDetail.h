/* bedDetail.h was originally generated by the autoSql program, which also
 * generated bedDetail.c and bedDetail.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef BEDDETAIL_H
#define BEDDETAIL_H

#include "asParse.h"

#define BEDDETAIL_NUM_COLS 14

struct bedDetail
/* Browser extensible data, with extended fields for detail page */
    {
    struct bedDetail *next;  /* Next in singly linked list. */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Short Name of item */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    unsigned thickStart;	/* Start of where display should be thick (start codon) */
    unsigned thickEnd;	/* End of where display should be thick (stop codon) */
    unsigned reserved;	/* Used as itemRgb as of 2004-11-22 */
    int blockCount;	/* Number of blocks */
    int *blockSizes;	/* Comma separated list of block sizes */
    int *chromStarts;	/* Start positions relative to chromStart */
    char *id;	/* ID to bed used in URL to link back */
    char *description;	/* Long description of item for the details page */
    };

struct bedDetail *bedDetailLoad(char **row);
/* Load a bedDetail from row fetched with select * from bedDetail
 * from database.  Dispose of this with bedDetailFree(). */

struct bedDetail *bedDetailLoadAll(char *fileName);
/* Load all bedDetail from whitespace-separated file.
 * Dispose of this with bedDetailFreeList(). */

struct bedDetail *bedDetailLoadAllByChar(char *fileName, char chopper);
/* Load all bedDetail from chopper separated file.
 * Dispose of this with bedDetailFreeList(). */

#define bedDetailLoadAllByTab(a) bedDetailLoadAllByChar(a, '\t');
/* Load all bedDetail from tab separated file.
 * Dispose of this with bedDetailFreeList(). */

struct bedDetail *bedDetailCommaIn(char **pS, struct bedDetail *ret);
/* Create a bedDetail out of a comma separated string.
 * This will fill in ret if non-null, otherwise will
 * return a new bedDetail */

void bedDetailFree(struct bedDetail **pEl);
/* Free a single dynamically allocated bedDetail such as created
 * with bedDetailLoad(). */

void bedDetailFreeList(struct bedDetail **pList);
/* Free a list of dynamically allocated bedDetail's */

void bedDetailOutput(struct bedDetail *el, FILE *f, char sep, char lastSep, int size);
/* Print out bedDetail.  Separate fields with sep. Follow last field with lastSep. */

#define bedDetailTabOut(el,f) bedDetailOutput(el,f,'\t','\n');
/* Print out bedDetail as a line in a tab-separated file. */

#define bedDetailCommaOut(el,f) bedDetailOutput(el,f,',',',');
/* Print out bedDetail as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

struct asObject *bedDetailAsObj();
// Return asObject describing fields of bedDetail

struct bedDetail *bedDetailLoadWithGaps(char **row, int size);
/* Load a bedDetail from row split from a file or from database,
   may have parts of BED not included.  Dispose of this with bedDetailFree(). */

struct bedDetail *bedDetailLineFileLoad (char **row, int size, struct lineFile *lf);
/* load from linefile line, with error checking */

#endif /* BEDDETAIL_H */

