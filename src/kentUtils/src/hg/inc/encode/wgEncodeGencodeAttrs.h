/* wgEncodeGencodeAttrs.h was originally generated by the autoSql program, which also 
 * generated wgEncodeGencodeAttrs.c and wgEncodeGencodeAttrs.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef WGENCODEGENCODEATTRS_H
#define WGENCODEGENCODEATTRS_H

#define WGENCODEGENCODEATTRS_NUM_COLS 13

struct wgEncodeGencodeAttrs
/* Basic set of attributes associated with all Gencode transcripts. */
    {
    struct wgEncodeGencodeAttrs *next;  /* Next in singly linked list. */
    char *geneId;	/* Gene identifier */
    char *geneName;	/* Gene name */
    char *geneType;	/* BioType of gene */
    char *geneStatus;	/* Status of gene */
    char *transcriptId;	/* Transcript identifier */
    char *transcriptName;	/* Transcript name */
    char *transcriptType;	/* BioType of transcript */
    char *transcriptStatus;	/* Status of transcript */
    char *havanaGeneId;	/* HAVANA identifier if gene is in HAVANA */
    char *havanaTranscriptId;	/* HAVANA identifier if transcript is in HAVANA */
    char *ccdsId;	/* CCDS identifier if transcript is in CCDS */
    int level;	/* GENCODE level: 1 = experimental confirmed, 2 = manual, 3 = automated */
    char *transcriptClass;	/* high level type of transcript */
    };

void wgEncodeGencodeAttrsStaticLoad(char **row, struct wgEncodeGencodeAttrs *ret);
/* Load a row from wgEncodeGencodeAttrs table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct wgEncodeGencodeAttrs *wgEncodeGencodeAttrsLoad(char **row);
/* Load a wgEncodeGencodeAttrs from row fetched with select * from wgEncodeGencodeAttrs
 * from database.  Dispose of this with wgEncodeGencodeAttrsFree(). */

struct wgEncodeGencodeAttrs *wgEncodeGencodeAttrsLoadAll(char *fileName);
/* Load all wgEncodeGencodeAttrs from whitespace-separated file.
 * Dispose of this with wgEncodeGencodeAttrsFreeList(). */

struct wgEncodeGencodeAttrs *wgEncodeGencodeAttrsLoadAllByChar(char *fileName, char chopper);
/* Load all wgEncodeGencodeAttrs from chopper separated file.
 * Dispose of this with wgEncodeGencodeAttrsFreeList(). */

#define wgEncodeGencodeAttrsLoadAllByTab(a) wgEncodeGencodeAttrsLoadAllByChar(a, '\t');
/* Load all wgEncodeGencodeAttrs from tab separated file.
 * Dispose of this with wgEncodeGencodeAttrsFreeList(). */

struct wgEncodeGencodeAttrs *wgEncodeGencodeAttrsCommaIn(char **pS, struct wgEncodeGencodeAttrs *ret);
/* Create a wgEncodeGencodeAttrs out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new wgEncodeGencodeAttrs */

void wgEncodeGencodeAttrsFree(struct wgEncodeGencodeAttrs **pEl);
/* Free a single dynamically allocated wgEncodeGencodeAttrs such as created
 * with wgEncodeGencodeAttrsLoad(). */

void wgEncodeGencodeAttrsFreeList(struct wgEncodeGencodeAttrs **pList);
/* Free a list of dynamically allocated wgEncodeGencodeAttrs's */

void wgEncodeGencodeAttrsOutput(struct wgEncodeGencodeAttrs *el, FILE *f, char sep, char lastSep);
/* Print out wgEncodeGencodeAttrs.  Separate fields with sep. Follow last field with lastSep. */

#define wgEncodeGencodeAttrsTabOut(el,f) wgEncodeGencodeAttrsOutput(el,f,'\t','\n');
/* Print out wgEncodeGencodeAttrs as a line in a tab-separated file. */

#define wgEncodeGencodeAttrsCommaOut(el,f) wgEncodeGencodeAttrsOutput(el,f,',',',');
/* Print out wgEncodeGencodeAttrs as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* WGENCODEGENCODEATTRS_H */

