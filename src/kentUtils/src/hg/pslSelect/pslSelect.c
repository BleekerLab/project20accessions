/* pslSelect - select records from a PSL file  */

/* Copyright (C) 2011 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */
#include "common.h"
#include "options.h"
#include "linefile.h"
#include "dystring.h"
#include "hash.h"
#include "localmem.h"
#include "psl.h"


/* command line option specifications */
static struct optionSpec optionSpecs[] = {
    {"qtPairs", OPTION_STRING},
    {"queries", OPTION_STRING},
    {"qtStart", OPTION_STRING},
    {"queryPairs", OPTION_STRING},
    {NULL, 0}
};

#define QT_PAIRS_MODE   1
#define QUERY_MODE      2
#define QUERY_PAIRS_MODE 3
#define QT_START        4

static int mode = 0;
static int isPairs = TRUE;

/* global data from command line */
static char *selectFile;

void usage()
/* Explain usage and exit. */
{
errAbort(
  "pslSelect - select records from a PSL file.\n"
  "\n"
  "usage:\n"
  "   pslSelect [options] inPsl outPsl\n"
  "\n"
  "Must specify a selection option\n"
  "\n"
  "Options:\n"
  "   -qtPairs=file - file is tab-separated qName and tName pairs to select\n"
  "   -queries=file - file has qNames to select\n"
  "   -queryPairs=file - file is tab-separated paris of qNames to select\n"
  "    with new qName to substitute in output file\n"
  "   -qtStart=file - file is tab-seperate rows of qName,tName,tStart\n"
  );
}

struct hash *loadSelect(char *selectFile)
/* load select file. */
{
struct hash *hash = hashNew(20);
char *row[2];
struct lineFile *lf = lineFileOpen(selectFile, TRUE);
int wordCount = isPairs ? 2 : 1;
while (lineFileNextRowTab(lf, row, wordCount))
    {
    char *value = isPairs ? row[1] : "";
    hashAdd(hash, row[0], lmCloneString(hash->lm, value));
    }
lineFileClose(&lf);
return hash;
}

struct hash *loadSelect3(char *selectFile)
/* load select file. */
{
struct hash *hash = hashNew(20);
char *row[3];
char buff[128];
struct lineFile *lf = lineFileOpen(selectFile, TRUE);
while (lineFileNextRowTab(lf, row, ArraySize(row)))
    {
    sprintf(buff, "%s%s",lmCloneString(hash->lm, row[1]),lmCloneString(hash->lm, row[2]));
    hashAdd(hash, row[0], lmCloneString(hash->lm, buff));
    }
lineFileClose(&lf);
return hash;
}

boolean pairSelected3(struct hash* selectHash, char *qName, char *tName, int tStart)
/* determine if the query/target/tStart triple is selected.  Handle the query
 * being paired to multiple targets */
{
char buff[128];
struct hashEl *hel = hashLookup(selectHash, qName);
while (hel != NULL)
    {
    char *target = hel->val;
    sprintf(buff,"%s%d",tName, tStart);
    if (sameString(target, buff))
        return TRUE;
    hel = hashLookupNext(hel);
    }
return FALSE;
}

struct hashEl *selectedItem(struct hash* selectHash, char *qName, char *tName)
/* determine if the item is selected.  Handle the query
 * being paired to multiple query */
{
struct hashEl *hel = hashLookup(selectHash, qName);
while (hel != NULL)
    {
    char *target = hel->val;
    if (mode == QUERY_MODE || mode == QUERY_PAIRS_MODE)
        return hel;
    if (mode == QT_PAIRS_MODE && sameString(target, tName))
        return hel;
    hel = hashLookupNext(hel);
    }
return NULL;
}

void pslSelect(char *inPsl, char *outPsl)
/* select psl */
{
struct hash *selectHash = NULL;
struct lineFile *inPslLf = pslFileOpen(inPsl);
FILE *outPslFh = mustOpen(outPsl, "w");
struct psl* psl;
struct hashEl *hel;

if (mode != QT_START)
    selectHash = loadSelect(selectFile);
else
    selectHash = loadSelect3(selectFile);
while ((psl = pslNext(inPslLf)) != NULL)
    {
    if (mode == QT_START)
        {
        if (pairSelected3(selectHash, psl->qName, psl->tName, psl->tStart))
            pslTabOut(psl, outPslFh);
        }
    else if ((hel = selectedItem(selectHash, psl->qName, psl->tName)) != NULL)
        {
        if (mode == QUERY_PAIRS_MODE)
            {
            freeMem(psl->qName);
            psl->qName = cloneString(hel->val);
            }
        pslTabOut(psl, outPslFh);
        }
    pslFree(&psl);
    }

carefulClose(&outPslFh);
lineFileClose(&inPslLf);
}

int main(int argc, char *argv[])
/* Process command line. */
{
optionInit(&argc, argv, optionSpecs);
if (argc != 3)
    usage();
if ((selectFile = optionVal("qtPairs", NULL)) != NULL)
    mode = QT_PAIRS_MODE;
else if ((selectFile = optionVal("queries", NULL)) != NULL)
    {
    mode = QUERY_MODE;
    isPairs = FALSE;
    }
else if ((selectFile = optionVal("queryPairs", NULL)) != NULL)
    mode = QUERY_PAIRS_MODE;
else if ((selectFile = optionVal("qtStart", NULL)) != NULL)
    mode = QT_START;
else
    errAbort("must specify option");

pslSelect(argv[1], argv[2]);

return 0;
}
/*
 * Local Variables:
 * c-file-style: "jkent-c"
 * End:
 */

