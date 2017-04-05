/* cgh.h was originally generated by the autoSql program, which also 
 * generated cgh.c and cgh.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef CGH_H
#define CGH_H

struct cgh
/* Comparative Genomic Hybridization data assembly position information */
    {
    struct cgh *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome name */
    unsigned chromStart;	/* position in nucleotides where feature starts on chromosome */
    unsigned chromEnd;	/* position in nucleotides where featrure stops on chromsome */
    char *name;	/* Name of the cell line (type 3 only) */
    float score;	/* hybridization score */
    unsigned type;	/* 1 - overall average, 2 - tissue average, 3 - single tissue */
    char *tissue;	/* Type of tissue cell line derived from (type 2 and type 3) */
    char *clone;	/* Name of clone */
    unsigned spot;	/* Spot number on array */
    };

void cghStaticLoad(char **row, struct cgh *ret);
/* Load a row from cgh table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct cgh *cghLoad(char **row);
/* Load a cgh from row fetched with select * from cgh
 * from database.  Dispose of this with cghFree(). */

struct cgh *cghLoadAll(char *fileName);
/* Load all cgh from a tab-separated file.
 * Dispose of this with cghFreeList(). */

struct cgh *cghCommaIn(char **pS, struct cgh *ret);
/* Create a cgh out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cgh */

void cghFree(struct cgh **pEl);
/* Free a single dynamically allocated cgh such as created
 * with cghLoad(). */

void cghFreeList(struct cgh **pList);
/* Free a list of dynamically allocated cgh's */

void cghOutput(struct cgh *el, FILE *f, char sep, char lastSep);
/* Print out cgh.  Separate fields with sep. Follow last field with lastSep. */

#define cghTabOut(el,f) cghOutput(el,f,'\t','\n');
/* Print out cgh as a line in a tab-separated file. */

#define cghCommaOut(el,f) cghOutput(el,f,',',',');
/* Print out cgh as a comma separated list including final comma. */

#endif /* CGH_H */

