/* symTest.h was originally generated by the autoSql program, which also 
 * generated symTest.c and symTest.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef SYMTEST_H
#define SYMTEST_H

#define SYMTEST_NUM_COLS 3

extern char *symTestCommaSepFieldNames;

enum symTestSex
    {
    symTestMale = 0,
    symTestFemale = 1,
    };
enum symTestSkills
    {
    symTestCProg = 0x0001,
    symTestJavaProg = 0x0002,
    symTestPythonProg = 0x0004,
    symTestAwkProg = 0x0008,
    };
struct symTest
/* test of enum and set symbolic columns */
    {
    struct symTest *next;  /* Next in singly linked list. */
    int id;	/* unique id */
    enum symTestSex sex;	/* enumerated column */
    unsigned skills;	/* set column */
    };

void symTestStaticLoad(char **row, struct symTest *ret);
/* Load a row from symTest table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct symTest *symTestLoad(char **row);
/* Load a symTest from row fetched with select * from symTest
 * from database.  Dispose of this with symTestFree(). */

struct symTest *symTestLoadAll(char *fileName);
/* Load all symTest from whitespace-separated file.
 * Dispose of this with symTestFreeList(). */

struct symTest *symTestLoadAllByChar(char *fileName, char chopper);
/* Load all symTest from chopper separated file.
 * Dispose of this with symTestFreeList(). */

#define symTestLoadAllByTab(a) symTestLoadAllByChar(a, '\t');
/* Load all symTest from tab separated file.
 * Dispose of this with symTestFreeList(). */

struct symTest *symTestCommaIn(char **pS, struct symTest *ret);
/* Create a symTest out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new symTest */

void symTestFree(struct symTest **pEl);
/* Free a single dynamically allocated symTest such as created
 * with symTestLoad(). */

void symTestFreeList(struct symTest **pList);
/* Free a list of dynamically allocated symTest's */

void symTestOutput(struct symTest *el, FILE *f, char sep, char lastSep);
/* Print out symTest.  Separate fields with sep. Follow last field with lastSep. */

#define symTestTabOut(el,f) symTestOutput(el,f,'\t','\n');
/* Print out symTest as a line in a tab-separated file. */

#define symTestCommaOut(el,f) symTestOutput(el,f,',',',');
/* Print out symTest as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* SYMTEST_H */

