/* txGraph.c was originally generated by the autoSql program, which also 
 * generated txGraph.h and txGraph.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "txGraph.h"


struct txGraph *txGraphLoad(char **row)
/* Load a txGraph from row fetched with select * from txGraph
 * from database.  Dispose of this with txGraphFree(). */
{
struct txGraph *ret;

AllocVar(ret);
ret->vertexCount = sqlUnsigned(row[5]);
ret->edgeCount = sqlUnsigned(row[7]);
ret->sourceCount = sqlSigned(row[9]);
ret->tName = cloneString(row[0]);
ret->tStart = sqlSigned(row[1]);
ret->tEnd = sqlSigned(row[2]);
ret->name = cloneString(row[3]);
safecpy(ret->strand, sizeof(ret->strand), row[4]);
{
int i;
char *s = row[6];
AllocArray(ret->vertices, ret->vertexCount);
for (i=0; i<ret->vertexCount; ++i)
    {
    s = sqlEatChar(s, '{');
    txVertexCommaIn(&s, &ret->vertices[i]);
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
}
{
int i;
char *s = row[8];
for (i=0; i<ret->edgeCount; ++i)
    {
    s = sqlEatChar(s, '{');
    slSafeAddHead(&ret->edgeList, txEdgeCommaIn(&s, NULL));
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
slReverse(&ret->edgeList);
}
{
int i;
char *s = row[10];
AllocArray(ret->sources, ret->sourceCount);
for (i=0; i<ret->sourceCount; ++i)
    {
    s = sqlEatChar(s, '{');
    txSourceCommaIn(&s, &ret->sources[i]);
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
}
return ret;
}

struct txGraph *txGraphLoadAll(char *fileName) 
/* Load all txGraph from a whitespace-separated file.
 * Dispose of this with txGraphFreeList(). */
{
struct txGraph *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[11];

while (lineFileRow(lf, row))
    {
    el = txGraphLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct txGraph *txGraphLoadAllByChar(char *fileName, char chopper) 
/* Load all txGraph from a chopper separated file.
 * Dispose of this with txGraphFreeList(). */
{
struct txGraph *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[11];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = txGraphLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct txGraph *txGraphCommaIn(char **pS, struct txGraph *ret)
/* Create a txGraph out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txGraph */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->tName = sqlStringComma(&s);
ret->tStart = sqlSignedComma(&s);
ret->tEnd = sqlSignedComma(&s);
ret->name = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->vertexCount = sqlUnsignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->vertices, ret->vertexCount);
for (i=0; i<ret->vertexCount; ++i)
    {
    s = sqlEatChar(s, '{');
    if(s[0] != '}')        txVertexCommaIn(&s, &ret->vertices[i]);
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
ret->edgeCount = sqlUnsignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
for (i=0; i<ret->edgeCount; ++i)
    {
    s = sqlEatChar(s, '{');
    if(s[0] != '}')        slSafeAddHead(&ret->edgeList, txEdgeCommaIn(&s,NULL));
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
slReverse(&ret->edgeList);
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
ret->sourceCount = sqlSignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->sources, ret->sourceCount);
for (i=0; i<ret->sourceCount; ++i)
    {
    s = sqlEatChar(s, '{');
    if(s[0] != '}')        txSourceCommaIn(&s, &ret->sources[i]);
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
*pS = s;
return ret;
}

void txGraphFree(struct txGraph **pEl)
/* Free a single dynamically allocated txGraph such as created
 * with txGraphLoad(). */
{
struct txGraph *el;

if ((el = *pEl) == NULL) return;
freeMem(el->tName);
freeMem(el->name);
freeMem(el->vertices);
txEdgeFreeList(&el->edgeList);
txSourceFreeInternals(el->sources, el->sourceCount);
freeMem(el->sources);
freez(pEl);
}

void txGraphFreeList(struct txGraph **pList)
/* Free a list of dynamically allocated txGraph's */
{
struct txGraph *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    txGraphFree(&el);
    }
*pList = NULL;
}

void txGraphOutput(struct txGraph *el, FILE *f, char sep, char lastSep) 
/* Print out txGraph.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->tStart);
fputc(sep,f);
fprintf(f, "%d", el->tEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->vertexCount);
fputc(sep,f);
{
int i;
/* Loading txVertex list. */
    {
    struct txVertex *it = el->vertices;
    if (sep == ',') fputc('{',f);
    for (i=0; i<el->vertexCount; ++i)
        {
        fputc('{',f);
        txVertexCommaOut(&it[i],f);
        fputc('}',f);
        fputc(',',f);
        }
    if (sep == ',') fputc('}',f);
    }
}
fputc(sep,f);
fprintf(f, "%u", el->edgeCount);
fputc(sep,f);
{
int i;
/* Loading txEdge list. */
    {
    struct txEdge *it = el->edgeList;
    if (sep == ',') fputc('{',f);
    for (i=0; i<el->edgeCount; ++i)
        {
        fputc('{',f);
        txEdgeCommaOut(it,f);
        it = it->next;
        fputc('}',f);
        fputc(',',f);
        }
    if (sep == ',') fputc('}',f);
    }
}
fputc(sep,f);
fprintf(f, "%d", el->sourceCount);
fputc(sep,f);
{
int i;
/* Loading txSource list. */
    {
    struct txSource *it = el->sources;
    if (sep == ',') fputc('{',f);
    for (i=0; i<el->sourceCount; ++i)
        {
        fputc('{',f);
        txSourceCommaOut(&it[i],f);
        fputc('}',f);
        fputc(',',f);
        }
    if (sep == ',') fputc('}',f);
    }
}
fputc(lastSep,f);
}

struct txVertex *txVertexCommaIn(char **pS, struct txVertex *ret)
/* Create a txVertex out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txVertex */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->position = sqlSignedComma(&s);
ret->type = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void txVertexOutput(struct txVertex *el, FILE *f, char sep, char lastSep) 
/* Print out txVertex.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->position);
fputc(sep,f);
fprintf(f, "%u", el->type);
fputc(lastSep,f);
}

struct txEdge *txEdgeCommaIn(char **pS, struct txEdge *ret)
/* Create a txEdge out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txEdge */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->startIx = sqlSignedComma(&s);
ret->endIx = sqlSignedComma(&s);
ret->type = sqlUnsignedComma(&s);
ret->evCount = sqlSignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
for (i=0; i<ret->evCount; ++i)
    {
    s = sqlEatChar(s, '{');
    if(s[0] != '}')        slSafeAddHead(&ret->evList, txEvidenceCommaIn(&s,NULL));
    s = sqlEatChar(s, '}');
    s = sqlEatChar(s, ',');
    }
slReverse(&ret->evList);
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
*pS = s;
return ret;
}

void txEdgeFree(struct txEdge **pEl)
/* Free a single dynamically allocated txEdge such as created
 * with txEdgeLoad(). */
{
struct txEdge *el;

if ((el = *pEl) == NULL) return;
txEvidenceFreeList(&el->evList);
freez(pEl);
}

void txEdgeFreeList(struct txEdge **pList)
/* Free a list of dynamically allocated txEdge's */
{
struct txEdge *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    txEdgeFree(&el);
    }
*pList = NULL;
}

void txEdgeOutput(struct txEdge *el, FILE *f, char sep, char lastSep) 
/* Print out txEdge.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->startIx);
fputc(sep,f);
fprintf(f, "%d", el->endIx);
fputc(sep,f);
fprintf(f, "%u", el->type);
fputc(sep,f);
fprintf(f, "%d", el->evCount);
fputc(sep,f);
{
int i;
/* Loading txEvidence list. */
    {
    struct txEvidence *it = el->evList;
    if (sep == ',') fputc('{',f);
    for (i=0; i<el->evCount; ++i)
        {
        fputc('{',f);
        txEvidenceCommaOut(it,f);
        it = it->next;
        fputc('}',f);
        fputc(',',f);
        }
    if (sep == ',') fputc('}',f);
    }
}
fputc(lastSep,f);
}

struct txEvidence *txEvidenceCommaIn(char **pS, struct txEvidence *ret)
/* Create a txEvidence out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txEvidence */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->sourceId = sqlSignedComma(&s);
ret->start = sqlSignedComma(&s);
ret->end = sqlSignedComma(&s);
*pS = s;
return ret;
}

void txEvidenceFree(struct txEvidence **pEl)
/* Free a single dynamically allocated txEvidence such as created
 * with txEvidenceLoad(). */
{
struct txEvidence *el;

if ((el = *pEl) == NULL) return;
freez(pEl);
}

void txEvidenceFreeList(struct txEvidence **pList)
/* Free a list of dynamically allocated txEvidence's */
{
struct txEvidence *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    txEvidenceFree(&el);
    }
*pList = NULL;
}

void txEvidenceOutput(struct txEvidence *el, FILE *f, char sep, char lastSep) 
/* Print out txEvidence.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->sourceId);
fputc(sep,f);
fprintf(f, "%d", el->start);
fputc(sep,f);
fprintf(f, "%d", el->end);
fputc(lastSep,f);
}

struct txSource *txSourceCommaIn(char **pS, struct txSource *ret)
/* Create a txSource out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new txSource */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->type = sqlStringComma(&s);
ret->accession = sqlStringComma(&s);
*pS = s;
return ret;
}

void txSourceFreeInternals(struct txSource *array, int count)
/* Free internals of a simple type txSource (one not put on a list). */
{
int i;
for (i=0; i<count; ++i)
    {
    struct txSource *el = &array[i];
    freeMem(el->type);
    freeMem(el->accession);
    }
}

void txSourceOutput(struct txSource *el, FILE *f, char sep, char lastSep) 
/* Print out txSource.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->type);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->accession);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

