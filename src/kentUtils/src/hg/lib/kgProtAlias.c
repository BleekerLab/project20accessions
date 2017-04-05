/* kgProtAlias.c was originally generated by the autoSql program, which also 
 * generated kgProtAlias.h and kgProtAlias.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "kgProtAlias.h"


void kgProtAliasStaticLoad(char **row, struct kgProtAlias *ret)
/* Load a row from kgProtAlias table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->kgID = row[0];
ret->displayID = row[1];
ret->alias = row[2];
}

struct kgProtAlias *kgProtAliasLoad(char **row)
/* Load a kgProtAlias from row fetched with select * from kgProtAlias
 * from database.  Dispose of this with kgProtAliasFree(). */
{
struct kgProtAlias *ret;

AllocVar(ret);
ret->kgID = cloneString(row[0]);
ret->displayID = cloneString(row[1]);
ret->alias = cloneString(row[2]);
return ret;
}

struct kgProtAlias *kgProtAliasLoadAll(char *fileName) 
/* Load all kgProtAlias from a whitespace-separated file.
 * Dispose of this with kgProtAliasFreeList(). */
{
struct kgProtAlias *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = kgProtAliasLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct kgProtAlias *kgProtAliasLoadAllByChar(char *fileName, char chopper) 
/* Load all kgProtAlias from a chopper separated file.
 * Dispose of this with kgProtAliasFreeList(). */
{
struct kgProtAlias *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = kgProtAliasLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct kgProtAlias *kgProtAliasCommaIn(char **pS, struct kgProtAlias *ret)
/* Create a kgProtAlias out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new kgProtAlias */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->kgID = sqlStringComma(&s);
ret->displayID = sqlStringComma(&s);
ret->alias = sqlStringComma(&s);
*pS = s;
return ret;
}

void kgProtAliasFree(struct kgProtAlias **pEl)
/* Free a single dynamically allocated kgProtAlias such as created
 * with kgProtAliasLoad(). */
{
struct kgProtAlias *el;

if ((el = *pEl) == NULL) return;
freeMem(el->kgID);
freeMem(el->displayID);
freeMem(el->alias);
freez(pEl);
}

void kgProtAliasFreeList(struct kgProtAlias **pList)
/* Free a list of dynamically allocated kgProtAlias's */
{
struct kgProtAlias *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    kgProtAliasFree(&el);
    }
*pList = NULL;
}

void kgProtAliasOutput(struct kgProtAlias *el, FILE *f, char sep, char lastSep) 
/* Print out kgProtAlias.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->kgID);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->displayID);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->alias);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

