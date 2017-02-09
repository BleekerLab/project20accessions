/* bed12Source.h was originally generated by the autoSql program, which also 
 * generated bed12Source.c and bed12Source.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2006 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef BED12SOURCE_H
#define BED12SOURCE_H

#define BED12SOURCE_NUM_COLS 13

struct bed12Source
/* Browser extensible data (12 fields) plus the source of this item. */
    {
    struct bed12Source *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome (or contig, scaffold, etc.) */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    unsigned thickStart;	/* Start of where display should be thick (start codon) */
    unsigned thickEnd;	/* End of where display should be thick (stop codon) */
    unsigned reserved;	/* Used as itemRgb as of 2004-11-22 */
    int blockCount;	/* Number of blocks */
    int *blockSizes;	/* Comma separated list of block sizes */
    int *chromStarts;	/* Start positions relative to chromStart */
    char *source;	/* Source of this item */
    };

struct bed12Source *bed12SourceLoad(char **row);
/* Load a bed12Source from row fetched with select * from bed12Source
 * from database.  Dispose of this with bed12SourceFree(). */

struct bed12Source *bed12SourceLoadAll(char *fileName);
/* Load all bed12Source from whitespace-separated file.
 * Dispose of this with bed12SourceFreeList(). */

struct bed12Source *bed12SourceLoadAllByChar(char *fileName, char chopper);
/* Load all bed12Source from chopper separated file.
 * Dispose of this with bed12SourceFreeList(). */

#define bed12SourceLoadAllByTab(a) bed12SourceLoadAllByChar(a, '\t');
/* Load all bed12Source from tab separated file.
 * Dispose of this with bed12SourceFreeList(). */

struct bed12Source *bed12SourceCommaIn(char **pS, struct bed12Source *ret);
/* Create a bed12Source out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new bed12Source */

void bed12SourceFree(struct bed12Source **pEl);
/* Free a single dynamically allocated bed12Source such as created
 * with bed12SourceLoad(). */

void bed12SourceFreeList(struct bed12Source **pList);
/* Free a list of dynamically allocated bed12Source's */

void bed12SourceOutput(struct bed12Source *el, FILE *f, char sep, char lastSep);
/* Print out bed12Source.  Separate fields with sep. Follow last field with lastSep. */

#define bed12SourceTabOut(el,f) bed12SourceOutput(el,f,'\t','\n');
/* Print out bed12Source as a line in a tab-separated file. */

#define bed12SourceCommaOut(el,f) bed12SourceOutput(el,f,',',',');
/* Print out bed12Source as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* BED12SOURCE_H */

