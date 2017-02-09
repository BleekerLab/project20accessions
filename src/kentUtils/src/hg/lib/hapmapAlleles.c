/* hapmapAlleles.c was originally generated by the autoSql program, which also 
 * generated hapmapAlleles.h and hapmapAlleles.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "hapmapAlleles.h"


void hapmapAllelesStaticLoad(char **row, struct hapmapAlleles *ret)
/* Load a row from hapmapAlleles table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->observed = row[6];
safecpy(ret->allele1, sizeof(ret->allele1), row[7]);
ret->homoCount1 = sqlUnsigned(row[8]);
ret->allele2 = row[9];
ret->homoCount2 = sqlUnsigned(row[10]);
ret->heteroCount = sqlUnsigned(row[11]);
}

struct hapmapAlleles *hapmapAllelesLoad(char **row)
/* Load a hapmapAlleles from row fetched with select * from hapmapAlleles
 * from database.  Dispose of this with hapmapAllelesFree(). */
{
struct hapmapAlleles *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->observed = cloneString(row[6]);
safecpy(ret->allele1, sizeof(ret->allele1), row[7]);
ret->homoCount1 = sqlUnsigned(row[8]);
ret->allele2 = cloneString(row[9]);
ret->homoCount2 = sqlUnsigned(row[10]);
ret->heteroCount = sqlUnsigned(row[11]);
return ret;
}

struct hapmapAlleles *hapmapAllelesLoadAll(char *fileName) 
/* Load all hapmapAlleles from a whitespace-separated file.
 * Dispose of this with hapmapAllelesFreeList(). */
{
struct hapmapAlleles *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[12];

while (lineFileRow(lf, row))
    {
    el = hapmapAllelesLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct hapmapAlleles *hapmapAllelesLoadAllByChar(char *fileName, char chopper) 
/* Load all hapmapAlleles from a chopper separated file.
 * Dispose of this with hapmapAllelesFreeList(). */
{
struct hapmapAlleles *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[12];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = hapmapAllelesLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct hapmapAlleles *hapmapAllelesCommaIn(char **pS, struct hapmapAlleles *ret)
/* Create a hapmapAlleles out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new hapmapAlleles */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->observed = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->allele1, sizeof(ret->allele1));
ret->homoCount1 = sqlUnsignedComma(&s);
ret->allele2 = sqlStringComma(&s);
ret->homoCount2 = sqlUnsignedComma(&s);
ret->heteroCount = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void hapmapAllelesFree(struct hapmapAlleles **pEl)
/* Free a single dynamically allocated hapmapAlleles such as created
 * with hapmapAllelesLoad(). */
{
struct hapmapAlleles *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->observed);
freeMem(el->allele2);
freez(pEl);
}

void hapmapAllelesFreeList(struct hapmapAlleles **pList)
/* Free a list of dynamically allocated hapmapAlleles's */
{
struct hapmapAlleles *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    hapmapAllelesFree(&el);
    }
*pList = NULL;
}

void hapmapAllelesOutput(struct hapmapAlleles *el, FILE *f, char sep, char lastSep) 
/* Print out hapmapAlleles.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->observed);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->allele1);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->homoCount1);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->allele2);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->homoCount2);
fputc(sep,f);
fprintf(f, "%u", el->heteroCount);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */
