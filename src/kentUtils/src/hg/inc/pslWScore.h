/* pslWScore.h was originally generated by the autoSql program, which also 
 * generated pslWScore.c and pslWScore.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef PSLWSCORE_H
#define PSLWSCORE_H

struct pslWScore
/* Summary info about a patSpace alignment with a score addition */
    {
    struct pslWScore *next;  /* Next in singly linked list. */
    unsigned match;	/* Number of bases that match that aren't repeats */
    unsigned misMatch;	/* Number of bases that don't match */
    unsigned repMatch;	/* Number of bases that match but are part of repeats */
    unsigned nCount;	/* Number of 'N' bases */
    unsigned qNumInsert;	/* Number of inserts in query */
    int qBaseInsert;	/* Number of bases inserted in query */
    unsigned tNumInsert;	/* Number of inserts in target */
    int tBaseInsert;	/* Number of bases inserted in target */
    char strand[3];	/* + or - for query strand. For mouse second +/- for genomic strand */
    char *qName;	/* Query sequence name */
    unsigned qSize;	/* Query sequence size */
    unsigned qStart;	/* Alignment start position in query */
    unsigned qEnd;	/* Alignment end position in query */
    char *tName;	/* Target sequence name */
    unsigned tSize;	/* Target sequence size */
    unsigned tStart;	/* Alignment start position in target */
    unsigned tEnd;	/* Alignment end position in target */
    unsigned blockCount;	/* Number of blocks in alignment */
    unsigned *blockSizes;	/* Size of each block */
    unsigned *qStarts;	/* Start of each block in query. */
    unsigned *tStarts;	/* Start of each block in target. */
    float score;	/* score field */
    };

struct pslWScore *pslWScoreLoad(char **row);
/* Load a pslWScore from row fetched with select * from pslWScore
 * from database.  Dispose of this with pslWScoreFree(). */

struct pslWScore *pslWScoreLoadAll(char *fileName);
/* Load all pslWScore from a tab-separated file.
 * Dispose of this with pslWScoreFreeList(). */

struct pslWScore *pslWScoreCommaIn(char **pS, struct pslWScore *ret);
/* Create a pslWScore out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pslWScore */

void pslWScoreFree(struct pslWScore **pEl);
/* Free a single dynamically allocated pslWScore such as created
 * with pslWScoreLoad(). */

void pslWScoreFreeList(struct pslWScore **pList);
/* Free a list of dynamically allocated pslWScore's */

void pslWScoreOutput(struct pslWScore *el, FILE *f, char sep, char lastSep);
/* Print out pslWScore.  Separate fields with sep. Follow last field with lastSep. */

#define pslWScoreTabOut(el,f) pslWScoreOutput(el,f,'\t','\n');
/* Print out pslWScore as a line in a tab-separated file. */

#define pslWScoreCommaOut(el,f) pslWScoreOutput(el,f,',',',');
/* Print out pslWScore as a comma separated list including final comma. */

#endif /* PSLWSCORE_H */

