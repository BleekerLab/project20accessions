/* hapmapAllelesCombined.h was originally generated by the autoSql program, which also 
 * generated hapmapAllelesCombined.c and hapmapAllelesCombined.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef HAPMAPALLELESCOMBINED_H
#define HAPMAPALLELESCOMBINED_H

#define HAPMAPALLELESCOMBINED_NUM_COLS 21

struct hapmapAllelesCombined
/* HapMap allele counts by population */
    {
    struct hapmapAllelesCombined *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome */
    unsigned chromStart;	/* Start position in chrom (0 based) */
    unsigned chromEnd;	/* End position in chrom (1 based) */
    char *name;	/* Reference SNP identifier from dbSnp */
    unsigned score;	/* Not used */
    char strand[2];	/* Which genomic strand contains the observed alleles */
    char *observed;	/* Observed string from genotype file */
    char allele1[2];	/* This allele has been observed */
    unsigned allele1CountCEU;	/* allele1 count for the CEU population */
    unsigned allele1CountCHB;	/* allele1 count for the CHB population */
    unsigned allele1CountJPT;	/* allele1 count for the JPT population */
    unsigned allele1CountYRI;	/* allele1 count for the YRI population */
    char *allele2;	/* This allele may not have been observed */
    unsigned allele2CountCEU;	/* allele2 count for the CEU population */
    unsigned allele2CountCHB;	/* allele2 count for the CHB population */
    unsigned allele2CountJPT;	/* allele2 count for the JPT population */
    unsigned allele2CountYRI;	/* allele2 count for the YRI population */
    unsigned heteroCountCEU;	/* Count of CEU individuals who are heterozygous */
    unsigned heteroCountCHB;	/* Count of CHB individuals who are heterozygous */
    unsigned heteroCountJPT;	/* Count of JPT individuals who are heterozygous */
    unsigned heteroCountYRI;	/* Count of YRI individuals who are heterozygous */
    };

void hapmapAllelesCombinedStaticLoad(char **row, struct hapmapAllelesCombined *ret);
/* Load a row from hapmapAllelesCombined table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct hapmapAllelesCombined *hapmapAllelesCombinedLoad(char **row);
/* Load a hapmapAllelesCombined from row fetched with select * from hapmapAllelesCombined
 * from database.  Dispose of this with hapmapAllelesCombinedFree(). */

struct hapmapAllelesCombined *hapmapAllelesCombinedLoadAll(char *fileName);
/* Load all hapmapAllelesCombined from whitespace-separated file.
 * Dispose of this with hapmapAllelesCombinedFreeList(). */

struct hapmapAllelesCombined *hapmapAllelesCombinedLoadAllByChar(char *fileName, char chopper);
/* Load all hapmapAllelesCombined from chopper separated file.
 * Dispose of this with hapmapAllelesCombinedFreeList(). */

#define hapmapAllelesCombinedLoadAllByTab(a) hapmapAllelesCombinedLoadAllByChar(a, '\t');
/* Load all hapmapAllelesCombined from tab separated file.
 * Dispose of this with hapmapAllelesCombinedFreeList(). */

struct hapmapAllelesCombined *hapmapAllelesCombinedCommaIn(char **pS, struct hapmapAllelesCombined *ret);
/* Create a hapmapAllelesCombined out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new hapmapAllelesCombined */

void hapmapAllelesCombinedFree(struct hapmapAllelesCombined **pEl);
/* Free a single dynamically allocated hapmapAllelesCombined such as created
 * with hapmapAllelesCombinedLoad(). */

void hapmapAllelesCombinedFreeList(struct hapmapAllelesCombined **pList);
/* Free a list of dynamically allocated hapmapAllelesCombined's */

void hapmapAllelesCombinedOutput(struct hapmapAllelesCombined *el, FILE *f, char sep, char lastSep);
/* Print out hapmapAllelesCombined.  Separate fields with sep. Follow last field with lastSep. */

#define hapmapAllelesCombinedTabOut(el,f) hapmapAllelesCombinedOutput(el,f,'\t','\n');
/* Print out hapmapAllelesCombined as a line in a tab-separated file. */

#define hapmapAllelesCombinedCommaOut(el,f) hapmapAllelesCombinedOutput(el,f,',',',');
/* Print out hapmapAllelesCombined as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* HAPMAPALLELESCOMBINED_H */

