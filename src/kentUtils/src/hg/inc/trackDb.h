/* trackDb.h was originally generated by the autoSql program, which also
 * generated trackDb.c and trackDb.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef TRACKDB_H
#define TRACKDB_H

struct trackDb;         // forward definition for use in cart.h

#include "common.h"

#ifndef JKSQL_H
#include "jksql.h"
#endif

#ifndef LINEFILE_H
#include "linefile.h"
#endif

#ifndef CART_H
#include "cart.h"
#endif

#define TRACKDB_NUM_COLS 21

// Forward definitions
struct tdbExtras;

struct trackDb
/* This describes an annotation track. */
    {
    struct trackDb *next;  /* Next in singly linked list.  Next sibling in tree. */
    char *track; /* Symbolic ID of Track - used in cart. Is tableName in database historically. */
    char *table; /* Symbolic ID of Table - used in database. Same as track usually. */
    char *shortLabel;	/* Short label displayed on left */
    char *type;	/* Track type: bed, psl, genePred, etc. */
    char *longLabel;	/* Long label displayed in middle */
    unsigned char visibility;	/* 0=hide, 1=dense, 2=full, 3=pack, 4=squish */
    float priority;	/* 0-100 - where to position.  0 is top */
    unsigned char colorR;	/* Color red component 0-255 */
    unsigned char colorG;	/* Color green component 0-255 */
    unsigned char colorB;	/* Color blue component 0-255 */
    unsigned char altColorR;	/* Light color red component 0-255 */
    unsigned char altColorG;	/* Light color green component 0-255 */
    unsigned char altColorB;	/* Light color blue component 0-255 */
    unsigned char useScore;	/* 1 if use score, 0 if not */
#ifndef	__cplusplus
    unsigned char private;	/* 1 if only want to show it on test site */
#else
    unsigned char priv;		/* don't conflict with C++ keyword */
#endif
    int restrictCount;	/* Number of chromosomes this is on (0=all though!) */
    char **restrictList;	/* List of chromosomes this is on */
    char *url;	/* URL to link to when they click on an item */
    char *html;	/* Some html to display when they click on an item */
    char *grp;	/* Which group track belongs to */
    unsigned char canPack;	/* 1 if can pack track display, 0 otherwise */
    char *settings;	/* Name/value pairs for track-specific stuff */
    struct hash *settingsHash;  /* Hash for settings. Not saved in database.
                                 * Don't use directly, rely on trackDbSetting to access. */
    /* additional info, determined from settings */
    char treeNodeType;          // bit map containing defining supertrack, composite and children
                                //     of same (may be parent & child)
    struct trackDb *parent;     // parent of composite or superTracks
    struct trackDb *subtracks;  // children of composite not supers. NOTE: only in one sl at a time!
    struct slRef *children;     // children of folders (superTracks) only.
                                // Needed as slRef since these children are on the main trackList
                                // and can't be in 2 sl's at once
    char *parentName;           // set if this is a supertrack member 
    boolean isShow;             // for supertracks: true if supertrack with pseudo-vis 'show'
    struct hash *overrides;     /* If not NULL, this is an override
                                 * entry.  It contains the names, but not the
                                 * values of the fields and settings that were
                                 * specified in the entry. */
    struct tdbExtras *tdbExtras;// This struct allows storing extra values which may be used
                                // multiple times within a single cgi. An example is the metadata
                                // looked up once in the metaDb and used again and again.
    };

#define FOLDER_MASK                      0x10
#define COMPOSITE_MASK                   0x20
#define MULTI_TRACK_MASK                 0x80
#define FOLDER_CHILD_MASK                0x01
#define COMPOSITE_CHILD_MASK             0x02
#define COMPOSITE_VIEW_MASK              0x04
#define MULTI_TRACK_CHILD_MASK           0x08
#define PARENT_MASK                      0xF0
#define CHILD_MASK                       0x0F
#define TREETYPE_MASK                    0xFF
#define PARENT_NODE(nodeType)            ((nodeType) & PARENT_MASK)
#define CHILD_NODE(nodeType)             ((nodeType) & CHILD_MASK)
#define FOLDER_NODE(nodeType)            ((nodeType) & FOLDER_MASK)
#define COMPOSITE_NODE(nodeType)         ((nodeType) & COMPOSITE_MASK)
#define MULTI_TRACK_NODE(nodeType)       ((nodeType) & MULTI_TRACK_MASK)
#define CONTAINER_NODE(nodeType)         ((nodeType) & (MULTI_TRACK_MASK | COMPOSITE_MASK))
#define FOLDER_CHILD_NODE(nodeType)      ((nodeType) & FOLDER_CHILD_MASK)
#define COMPOSITE_CHILD_NODE(nodeType)   ((nodeType) & COMPOSITE_CHILD_MASK)
#define COMPOSITE_VIEW_NODE(nodeType)    ((nodeType) & COMPOSITE_VIEW_MASK)
#define MULTI_TRACK_CHILD_NODE(nodeType) ((nodeType) & MULTI_TRACK_CHILD_MASK)
#define CONTAINER_CHILD_NODE(nodeType)   ((nodeType) & \
                                                   (MULTI_TRACK_CHILD_MASK | COMPOSITE_CHILD_MASK))
#define INDEPENDENT_NODE(nodeType)      (((nodeType) & TREETYPE_MASK) == 0 )
#define SOLO_NODE(nodeType)             (((nodeType) & TREETYPE_MASK) <= FOLDER_CHILD_MASK)
//#define tdbIsParent(tdb)     ((tdb)->subtracks)
//#define tdbIsChild(tdb)      ((tdb)->parent   )
//#define tdbIsTreeLeaf(tdb)   ( CHILD_NODE((tdb)->treeNodeType) && !tdbIsParent(tdb))
//#define tdbIsTreeRoot(tdb)   (PARENT_NODE((tdb)->treeNodeType) && !tdbIsChild(tdb) )
//#define tdbIsTreeBranch(tdb) (  !INDEPENDENT_NODE((tdb)->treeNodeType)
//                             &&  tdbIsParent(tdb) &&  tdbIsChild(tdb))
//#define tdbIsNotInTree(tdb)  (   INDEPENDENT_NODE((tdb)->treeNodeType)
//                             && !tdbIsParent(tdb) && !tdbIsChild(tdb))

// --- Folders are superTracks.  Currently only one level deep
INLINE void tdbMarkAsFolder(struct trackDb *tdb)
// Marks a trackDb struct as a supertrack
{
tdb->treeNodeType |= FOLDER_MASK;
}
#define tdbMarkAsSuperTrack(tdb) tdbMarkAsFolder(tdb)

INLINE void tdbMarkAsFolderChild(struct trackDb *tdb)
// Marks a trackDb struct as a child of a folder
{
tdb->treeNodeType |= FOLDER_CHILD_MASK;
}
#define tdbMarkAsSuperTrackChild(tdb) tdbMarkAsFolderChild(tdb)

INLINE boolean tdbIsFolder(struct trackDb *tdb)
// Is this trackDb struct marked as a folder ?
{
return tdb && FOLDER_NODE(tdb->treeNodeType);  // && tdb->children
//  NOTE: The children list is not always filled in, but should be
}
#define tdbIsSuper(tdb) tdbIsFolder(tdb)
#define tdbIsSuperTrack(tdb) tdbIsFolder(tdb)

INLINE boolean tdbIsFolderContent(struct trackDb *tdb)
// Is this trackDb struct marked as a contained in a folder ?
{
return tdb && tdb->parent && FOLDER_CHILD_NODE(tdb->treeNodeType);
}
#define tdbIsSuperTrackChild(tdb) tdbIsFolderContent(tdb)

INLINE struct trackDb *tdbGetImmediateFolder(struct trackDb *tdb)
// Return closest ancestor who is a folder track.
{
struct trackDb *parent = tdb->parent;
for ( ; parent != NULL && !tdbIsFolder(parent); parent = parent->parent)
    ;
return parent;
}
#define tdbGetSuperTrack(tdb) tdbGetImmediateFolder(tdb)


// --- Composites are 2 or 3 level containers of tracks organized into a single hgTrackUi cfg page
INLINE void tdbMarkAsComposite( struct trackDb *tdb)
// Marks a trackDb struct as a composite track
{
tdb->treeNodeType |= COMPOSITE_MASK;
}

INLINE void tdbMarkAsCompositeView( struct trackDb *tdb)
// Marks a trackDb struct as a view of a composite track
{
tdb->treeNodeType |= COMPOSITE_VIEW_MASK;
}

INLINE void tdbMarkAsCompositeChild( struct trackDb *tdb)
// Marks a trackDb struct as a child or subtrack of a composite track
{
tdb->treeNodeType |= COMPOSITE_CHILD_MASK;
}
#define tdbMarkAsCompositeSubtrack(tdb) tdbMarkAsCompositeChild(tdb)

INLINE boolean tdbIsComposite( struct trackDb *tdb)
// Is this trackDb struct marked as a composite with children ?
{
return tdb && tdb->subtracks && COMPOSITE_NODE( tdb->treeNodeType);
}

INLINE boolean tdbIsCompositeView(struct trackDb *tdb)
// Is this trackDb struct marked as a view of a composite track ?
{
return tdb && tdb->parent && tdb->subtracks && COMPOSITE_VIEW_NODE( tdb->treeNodeType);
}

INLINE boolean tdbIsCompositeChild(struct trackDb *tdb)
// Is this trackDb struct marked as a child of a composite track ?
{
return tdb && tdb->parent && COMPOSITE_CHILD_NODE(tdb->treeNodeType);
}
#define tdbIsCompositeSubtrack(tdb) tdbIsCompositeChild(tdb)

INLINE struct trackDb *tdbGetComposite(struct trackDb *tdb)
// Return closest ancestor who is a composite track.
{
struct trackDb *parent = tdb->parent;
for ( ; parent != NULL && !tdbIsComposite(parent); parent = parent->parent)
    ;
return parent;
}


// --- MultiTracks are container tracks with one level of subtracks
 //                combined into a unified hgTracks image track
INLINE void tdbMarkAsMultiTrack( struct trackDb *tdb)
// Marks a trackDb struct as a multiTrack (like multiWig)
{
tdb->treeNodeType |= MULTI_TRACK_MASK;
}

INLINE void tdbMarkAsMultiTrackChild( struct trackDb *tdb)
// Marks a trackDb struct as a child of a multiTrack (like multiWig)
{
tdb->treeNodeType |= MULTI_TRACK_CHILD_MASK;
}
#define tdbMarkAsMultiTrackSubtrack(tdb) tdbMarkAsMultiTrackChild(tdb)

INLINE boolean tdbIsMultiTrack( struct trackDb *tdb)
// Is this trackDb struct marked as a multiTrack (like multiWig) ?
{
return tdb && tdb->subtracks && MULTI_TRACK_NODE( tdb->treeNodeType);
}

INLINE boolean tdbIsMultiTrackChild(struct trackDb *tdb)
// Is this trackDb struct marked as a child of a multiTrack (like multiWig) ?
{
return tdb && tdb->parent && MULTI_TRACK_CHILD_NODE(tdb->treeNodeType);
}
#define tdbIsMultiTrackSubtrack(tdb) tdbIsMultiTrackChild(tdb)

INLINE struct trackDb *tdbGetMultiTrack(struct trackDb *tdb)
// Return closest ancestor who is a multiTrack.
{
struct trackDb *parent = tdb->parent;
for ( ; parent != NULL && !tdbIsMultiTrack(parent); parent = parent->parent)
    ;
return parent;
}


// --- CONTAINERS are composites or multiTracks, which behave in similar ways thru some code paths
INLINE boolean tdbIsContainer( struct trackDb *tdb)
// Is this trackDb struct marked as a composite or multiTrack with children ?
{
return tdb && tdb->subtracks && CONTAINER_NODE(tdb->treeNodeType);
}

INLINE boolean tdbIsContainerChild(struct trackDb *tdb)
// Is this trackDb struct marked as a child of a composite or multiTrack ?
{
return tdb && tdb->parent && CONTAINER_CHILD_NODE(tdb->treeNodeType);
}
#define tdbIsSubtrack(tdb) tdbIsContainerChild(tdb)

INLINE struct trackDb *tdbGetContainer(struct trackDb *tdb)
// Return closest ancestor who is a container track.
{
struct trackDb *parent = tdb->parent;
for ( ; parent != NULL && !tdbIsContainer(parent); parent = parent->parent)
    ;
return parent;
}

// Solo (or stand alone) tracks are non-containers which may only be contained by folders
INLINE boolean tdbIsSoloTrack(struct trackDb *tdb)
// Is this trackDb struct marked as a solo so it should have data
{
return tdb && SOLO_NODE(tdb->treeNodeType);
}
#define tdbIsStandAlone(tdb) tdbIsSoloTrack(tdb)
#define tdbIsDataTrack(tdb) (tdbIsSoloTrack(tdb) || tdbIsSubtrack(tdb))

// TrackUi Top level means composite, multitrack or solo
// These are not folders, views or subtracks.
#define tdbIsTrackUiTopLevel(tdb) (tdbIsContainer(tdb) || tdbIsSoloTrack(tdb))

#define DOWNLOADS_ONLY_TYPE  "downloadsOnly"
INLINE boolean tdbIsDownloadsOnly(struct trackDb *tdb)
// Is this a downloadsOnly tdb
{
return (tdb && sameWord(tdb->type,DOWNLOADS_ONLY_TYPE));
}


struct trackDb *trackDbLoad(char **row);
/* Load a trackDb from row fetched with select * from trackDb
 * from database.  Dispose of this with trackDbFree(). */

struct trackDb *trackDbLoadAll(char *fileName);
/* Load all trackDb from whitespace-separated file.
 * Dispose of this with trackDbFreeList(). */

struct trackDb *trackDbLoadWhere(struct sqlConnection *conn, char *table,
	char *where);
/* Load all trackDb from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with trackDbFreeList(). */

struct trackDb *trackDbLoadAllByChar(char *fileName, char chopper);
/* Load all trackDb from chopper separated file.
 * Dispose of this with trackDbFreeList(). */

#define trackDbLoadAllByTab(a) trackDbLoadAllByChar(a, '\t');
/* Load all trackDb from tab separated file.
 * Dispose of this with trackDbFreeList(). */

struct trackDb *trackDbCommaIn(char **pS, struct trackDb *ret);
/* Create a trackDb out of a comma separated string.
 * This will fill in ret if non-null, otherwise will
 * return a new trackDb */

void trackDbFree(struct trackDb **pEl);
/* Free a single dynamically allocated trackDb such as created
 * with trackDbLoad(). */

void trackDbFreeList(struct trackDb **pList);
/* Free a list of dynamically allocated trackDb's */

void trackDbOutput(struct trackDb *el, FILE *f, char sep, char lastSep);
/* Print out trackDb.  Separate fields with sep. Follow last field with lastSep. */

#define trackDbTabOut(el,f) trackDbOutput(el,f,'\t','\n');
/* Print out trackDb as a line in a tab-separated file. */

#define trackDbCommaOut(el,f) trackDbOutput(el,f,',',',');
/* Print out trackDb as a comma separated list including final comma. */

/* ----------- End of AutoSQL generated code --------------------- */

struct trackDb *trackDbNew();
/* Allocate a new trackDb with just very minimal stuff filled in. */

int trackDbCmp(const void *va, const void *vb);
/* Sort track by priority. */

void trackDbOverridePriority(struct hash *tdHash, char *priorityRa);
/* Override priority settings using a ra file. */

struct trackDb *trackDbFromRa(char *raFile, char *releaseTag);
/* Load track info from ra file into list.  If releaseTag is non-NULL
 * then only load tracks that mesh with release. */

struct trackDb *trackDbFromOpenRa(struct lineFile *lf, char *releaseTag);
/* Load track info from ra file already opened as lineFile into list.  If releaseTag is
 * non-NULL then only load tracks that mesh with release. */

void trackDbPolish(struct trackDb *bt);
/* Fill in missing values with defaults. */

void trackDbFieldsFromSettings(struct trackDb *td);
/* Update trackDb fields from settings hash */

char *trackDbLocalSetting(struct trackDb *tdb, char *name);
/* Return setting from tdb, but *not* any of it's parents. */

struct hash *trackDbHashSettings(struct trackDb *tdb);
/* Force trackDb to hash up it's settings.  Usually this is just
 * done on demand. Returns settings hash. */

struct hash *trackDbSettingsFromString(char *string);
/* Return hash of key/value pairs from string.  Differs
 * from raFromString in that it passes the key/val
 * pair through the backwards compatability routines. */

char *trackDbSetting(struct trackDb *tdb, char *name);
/* Return setting string or NULL if none exists. */

void trackDbAddSetting(struct trackDb *bt, char *name, char *val);
/* Add a setting to a trackDb rec */

boolean trackDbSettingOn(struct trackDb *tdb, char *name);
/* Return true if a tdb setting is "on" "true" or "enabled". */

char *trackDbRequiredSetting(struct trackDb *tdb, char *name);
/* Return setting string or squawk and die. */

char *trackDbSettingOrDefault(struct trackDb *tdb, char *name, char *defaultVal);
/* Return setting string, or defaultVal if none exists */

struct hashEl *trackDbSettingsLike(struct trackDb *tdb, char *wildStr);
/* Return a list of settings whose names match wildStr (may contain wildcard
 * characters).  Free the result with hashElFreeList. */

float trackDbFloatSettingOrDefault(struct trackDb *tdb, char *name, float defaultVal);
/* Return setting, convert to a float, or defaultVal if none exists */

void trackDbSuperMarkup(struct trackDb *tdbList);
/* Get info from supertrack setting.  There are 2 forms:
 * Parent:   'supertrack on [show]'
 * Child:    'supertrack <parent> [vis]
 * Returns NULL if there is no such setting */

char *trackDbInclude(char *raFile, char *line, char **releaseTag);
/* Get include filename from trackDb line.
   Return NULL if line doesn't contain include */

char *trackDbOrigAssembly(struct trackDb *tdb);
/* return setting from trackDb, if any */

void trackDbPrintOrigAssembly(struct trackDb *tdb, char *database);
/* Print lift information from trackDb, if any */

// Not all track types have separate configuration
typedef enum _eCfgType
    {
    cfgNone     =0,
    cfgBedScore =1,
    cfgWig      =2,
    cfgWigMaf   =3,
    cfgPeak     =4,
    cfgGenePred =5,
    cfgChain    =6,
    cfgNetAlign =7,
    cfgBedFilt  =8,
    cfgBam      =9,
    cfgPsl      =10,
    cfgVcf      =11,
    cfgSnake    =12,
    cfgUndetermined // Not specifically denied, but not determinable in lib code
    } eCfgType;

eCfgType cfgTypeFromTdb(struct trackDb *tdb, boolean warnIfNecessary);
/* determine what kind of track specific configuration is needed,
   warn if not multi-view compatible */

int configurableByAjax(struct trackDb *tdb, eCfgType cfgTypeIfKnown);
// Is this track configurable by right-click popup, or in hgTrackUi subCfg?
// returns 0 = nothing to cfg; <0=blocked via ajax; >0=allowed and will be cfgType if determinable

void trackDbOverride(struct trackDb *td, struct trackDb *overTd);
/* apply an trackOverride trackDb entry to a trackDb entry */

#ifdef OLD
char *trackDbCompositeSettingByView(struct trackDb *parentTdb, char* view, char *name);
/* Get a trackDb setting at the view level for a multiview composite.
   returns a string that must be freed */
#endif /* OLD */

char *trackDbSettingByView(struct trackDb *tdb, char *name);
/* For a subtrack of a multiview composite, get a setting stored in the parent settingByView.
   returns a string that must be freed */

#define trackDbSettingClosestToHome(tdb, name) trackDbSetting(tdb, name)

#ifdef OLD
char *trackDbSettingClosestToHome(struct trackDb *tdb, char *name);
/* Look for a trackDb setting from lowest level on up through chain of ancestors. */
#endif /* OLD */

char *trackDbSettingClosestToHomeOrDefault(struct trackDb *tdb, char *name, char *defaultVal);
/* Look for a trackDb setting (or default) from lowest level on up through chain of ancestors. */

boolean trackDbSettingClosestToHomeOn(struct trackDb *tdb, char *name);
/* Return true if a tdb setting closest to home is "on" "true" or "enabled". */

struct trackDb *subTdbFind(struct trackDb *parent,char *table);
/* Return subTrack tdb if it exists in parent. */

struct trackDb *tdbFindOrCreate(char *db,struct trackDb *parent,char *table);
/* Find or creates the tdb for this table. May return NULL. */

boolean tdbIsView(struct trackDb *tdb,char **viewName);
// Is this tdb a view?  Will fill viewName if provided

char *tdbGetViewName(struct trackDb *tdb);
// returns NULL the view name for view or child track (do not free)

void parseColor(char *text, unsigned char *r, unsigned char *g, unsigned char *b);
/* Turn comma-separated string of three numbers into three
 * color components. */

int parentTdbAbandonTablelessChildren(char *db, struct trackDb *parentTdb);
/* abandons tableless children from a container tdb, such as a composite
   returns count of children that have been abandoned */

struct trackDb *trackDbLinkUpGenerations(struct trackDb *tdbList);
/* Convert a list to a forest - filling in parent and subtrack pointers.
 * The exact topology of the forest is a little complex due to the
 * fact there are two "inheritance" systems - the superTrack system
 * and the subTrack system.  In the superTrack system (which is on it's
 * way out)  the superTrack's themselves have the tag:
 *     superTrack on
 * and the children of superTracks have the tag:
 *     superTrack parentName
 * In the subTrack system the parents have the tag:
 *     compositeTrack on
 * and the children have the tag:
 *     subTrack parentName
 * In this routine the subtracks are removed from the list, and stuffed into
 * the subtracks lists of their parents.  The highest level parents stay on
 * the list.  There can be multiple levels of inheritance.
 *    For the supertracks the _parents_ are removed from the list.  The only
 * reference to them in the returned forest is that they are in the parent
 * field of their children.  The parents of supertracks have no subtracks
 * after this call currently. */

void trackDbPrioritizeContainerItems(struct trackDb *tdbList);
/* Set priorities in containers if they have no priorities already set
   priorities are based upon 'sortOrder' setting or else shortLabel */

void trackDbAddTableField(struct trackDb *tdbList);
/* Add table field by looking it up in settings.  */

struct slRef *trackDbListGetRefsToDescendants(struct trackDb *tdbForest);
/* Return reference list to everything in forest. Do slFreeList when done. */

struct slRef *trackDbListGetRefsToDescendantLeaves(struct trackDb *tdbForest);
/* Return reference list all leaves in forest. Do slFreeList when done. */

int trackDbRefCmp(const void *va, const void *vb);
/* Do trackDbCmp on list of references as opposed to actual trackDbs. */

int trackDbCountDescendants(struct trackDb *tdb);
/* Count the number of tracks in subtracks list and their subtracks too . */

int trackDbCountDescendantLeaves(struct trackDb *tdb);
/* Count the number of leaves in children list and their children. */

struct trackDb *trackDbTopLevelSelfOrParent(struct trackDb *tdb);
/* Look for a parent who is a composite or multiTrack track and return that.  Failing that
 * just return self. */

boolean trackDbUpdateOldTag(char **pTag, char **pVal);
/* Look for obscolete tags and update them to new format.  Return TRUE if any update
 * is done.  Will allocate fresh memory for new tag and val if updated. */

boolean trackDbCheckValidRelease(char *tag);
/* check to make sure release tag is valid */

struct slName *trackDbLocalSettingsWildMatch(struct trackDb *tdb, char *expression);
// Return local settings that match expression else NULL.  In alpha order.

struct slName *trackDbSettingsWildMatch(struct trackDb *tdb, char *expression);
// Return settings in tdb tree that match expression else NULL.  In alpha order, no duplicates.

// Forward defs for tdbExtras
struct mdbObj;
struct _membersForAll;
struct _membership;

struct tdbExtras
#define TDB_EXTRAS_EMPTY_STATE 666
// Struct for misc. data collected/calculated during CGI track setup that are cached for later use.
// These extras are primarily used in hgTracks & hgTrackUi but can be used and expanded as needed.
// CGI developers are encouraged to add to this structure for their own needs.
    {
    int fourState; // hgTrackUi subtracks use 4 state checkboxes (checked/un by enabled/dis)
    boolean reshapedComposite; // hgTracks should not "reshape" composites more than once.
    struct mdbObj *mdb;        // several CGIs need repeated access to a tracks metadata
    struct _membersForAll *membersForAll; // hgTrackUi composites collect all view/dimension info
    struct _membership *membership;       // hgTrackUi subtracks have individual membership info

    // Developer: please add your useful data that is costly to calculate/retrieve more than once
    };

void tdbExtrasFree(struct tdbExtras **pTdbExtras);
// Frees the tdbExtras structure

int tdbExtrasFourState(struct trackDb *tdb);
// Returns subtrack four state if known, else TDB_EXTRAS_EMPTY_STATE

void tdbExtrasFourStateSet(struct trackDb *tdb,int fourState);
// Sets subtrack four state

boolean tdbExtrasReshapedComposite(struct trackDb *tdb);
// Returns TRUE if composite has been declared as reshaped, else FALSE.

void tdbExtrasReshapedCompositeSet(struct trackDb *tdb);
// Declares that the composite has been reshaped.

struct mdbObj *tdbExtrasMdb(struct trackDb *tdb);
// Returns mdb metadata if already known, else NULL

void tdbExtrasMdbSet(struct trackDb *tdb,struct mdbObj *mdb);
// Sets the mdb metadata structure for later retrieval.

struct _membersForAll *tdbExtrasMembersForAll(struct trackDb *tdb);
// Returns composite view/dimension members for all, else NULL.

void tdbExtrasMembersForAllSet(struct trackDb *tdb, struct _membersForAll *membersForAll);
// Sets the composite view/dimensions members for all for later retrieval.

struct _membership *tdbExtrasMembership(struct trackDb *tdb);
// Returns subtrack membership if already known, else NULL

void tdbExtrasMembershipSet(struct trackDb *tdb,struct _membership *membership);
// Sets the subtrack membership for later retrieval.

char *tdbBigFileName(struct sqlConnection *conn, struct trackDb *tdb);
// Return file name associated with bigWig.  Do a freeMem on returned string when done.

boolean rTdbTreeCanPack(struct trackDb *tdb);
// Trees can pack as all or none, since they can share vis.

void tdbSetCartVisibility(struct trackDb *tdb, struct cart *cart, char *vis);
// Set visibility in the cart. Handles all the complications necessary for subtracks.

// More INLINES which depend on what the definition of "is" is
INLINE boolean tdbIsBigBed(struct trackDb *tdb)
// Local test to see if something is big bed.  Handles hub tracks unlike hIsBigBed.
{
return startsWithWord("bigBed", tdb->type);
}

INLINE boolean tdbIsBigWig(struct trackDb *tdb)
// Local test to see if something is big bed.  Handles hub tracks unlike hIsBigBed.
{
return startsWithWord("bigWig", tdb->type);
}

INLINE boolean tdbIsBam(struct trackDb *tdb)
// Return TRUE if tdb corresponds to a BAM file.
{
return startsWithWord("bam", tdb->type);
}

INLINE boolean tdbIsVcf(struct trackDb *tdb)
// Return TRUE if tdb corresponds to a VCF file.
{
return startsWithWord("vcfTabix", tdb->type) || startsWithWord("vcf", tdb->type);
}

boolean trackDbSettingBlocksConfiguration(struct trackDb *tdb, boolean onlyAjax);
// Configuration dialogs may be explicitly blocked in tracDb settings

#endif /* TRACKDB_H */
