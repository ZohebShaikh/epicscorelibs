/* $Id$
 *
 *	Author:		Marty Kraimer
 *      Date:           06-08-93
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 * Modification Log:
 * -----------------
 * .01  06-08-93	mrk	Replace dbManipulate
 * .02  06-07-95	mrk	Get rid of default.dctsdr info
 */

#ifndef INCdbStaticLibh
#define INCdbStaticLibh 1

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <ellLib.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbBase.h>
#include <link.h>
#include <errMdef.h>

/*Field types as seen by static database access clients*/
#define DCT_STRING	0
#define DCT_INTEGER	1
#define DCT_REAL	2
#define DCT_MENU	3
#define DCT_MENUFORM	4
#define DCT_INLINK	5
#define DCT_OUTLINK	6
#define DCT_FWDLINK	7
#define DCT_NOACCESS	8

/*Link types as seen by static database access clients*/
#define DCT_LINK_CONSTANT	0
#define DCT_LINK_FORM		1
#define DCT_LINK_PV		2
#define DCT_LINK_DEVICE		3

/*options for dbRead and dbWrite*/
#define DB_RECDES_IO		0x1
#define DB_RECORD_IO		0x2

typedef dbBase DBBASE;

typedef struct{
	DBBASE		*pdbbase;
	dbRecDes	*precdes;
	dbFldDes	*pflddes;
	dbRecordNode	*precnode;
	void	 	*pfield;
	char		*message;
	short		indfield;
	void		*formpvt;
} DBENTRY;

/* Static database access routines*/
DBBASE *dbAllocBase(void);
void dbFreeBase(DBBASE *pdbbase);
DBENTRY *dbAllocEntry(DBBASE *pdbbase);
void dbFreeEntry(DBENTRY *pdbentry);
void dbInitEntry(DBBASE *pdbbase,DBENTRY *pdbentry);
void dbFinishEntry(DBENTRY *pdbentry);
DBENTRY *dbCopyEntry(DBENTRY *pdbentry);

long dbReadDatabase(DBBASE **ppdbbase,const char *filename,const char *path);
long dbReadDatabaseFP(DBBASE **ppdbbase,FILE *fp,const char *path);
long dbPath(DBBASE *pdbbase,const char *path);
long dbAddPath(DBBASE *pdbbase,const char *path);
long dbWriteRecord(DBBASE *ppdbbase,const char *filename,
	char *precdesname,int level);
long dbWriteRecordFP(DBBASE *ppdbbase,FILE *fp,
	char *precdesname,int level);
long dbWriteMenu(DBBASE *pdbbase,const char *filename,char *menuName);
long dbWriteMenuFP(DBBASE *pdbbase,FILE *fp,char *menuName);
long dbWriteRecDes(DBBASE *pdbbase,const char *filename,char *recdesName);
long dbWriteRecDesFP(DBBASE *pdbbase,FILE *fp,char *recdesName);
long dbWriteDevice(DBBASE *pdbbase,const char *filename);
long dbWriteDeviceFP(DBBASE *pdbbase,FILE *fp);
long dbWriteDriver(DBBASE *pdbbase,const char *filename);
long dbWriteDriverFP(DBBASE *pdbbase,FILE *fp);
long dbWriteBreaktable(DBBASE *pdbbase,const char *filename);
long dbWriteBreaktableFP(DBBASE *pdbbase,FILE *fp);

/*Following two routines are obsolete. For now dbRead calls dbAsciiRead.*/
/*  dbWrite does nothing						*/
long dbRead(DBBASE *pdbbase,FILE *fp);
long dbWrite(DBBASE *pdbbase,FILE *fpdctsdr,FILE *fp);

long dbFindRecdes(DBENTRY *pdbentry,char *recdesname);
long dbFirstRecdes(DBENTRY *pdbentry);
long dbNextRecdes(DBENTRY *pdbentry);
char *dbGetRecdesName(DBENTRY *pdbentry);
int  dbGetNRecdes(DBENTRY *pdbentry);

long dbCreateRecord(DBENTRY *pdbentry,char *precordName);
long dbDeleteRecord(DBENTRY *pdbentry);
long dbFindRecord(DBENTRY *pdbentry,char *precordName);
long dbFirstRecord(DBENTRY *pdbentry); /*first of record type*/
long dbNextRecord(DBENTRY *pdbentry);
int  dbGetNRecords(DBENTRY *pdbentry);
char *dbGetRecordName(DBENTRY *pdbentry);
long dbRenameRecord(DBENTRY *pdbentry,char *newName);

long dbFirstFielddes(DBENTRY *pdbentry,int dctonly);
long dbNextFielddes(DBENTRY *pdbentry,int dctonly);
int  dbGetFieldType(DBENTRY *pdbentry);
int  dbGetNFields(DBENTRY *pdbentry,int dctonly);
char *dbGetFieldName(DBENTRY *pdbentry);
char *dbGetDefault(DBENTRY *pdbentry);
char *dbGetString(DBENTRY *pdbentry);
char *dbGetPrompt(DBENTRY *pdbentry);
int dbGetPromptGroup(DBENTRY *pdbentry);

long dbFindField(DBENTRY *pdbentry,char *pfieldName);
char *dbGetString(DBENTRY *pdbentry);
long dbPutString(DBENTRY *pdbentry,char *pstring);
char *dbVerify(DBENTRY *pdbentry,char *pstring);
char *dbGetRange(DBENTRY *pdbentry);
int  dbIsDefaultValue(DBENTRY *pdbentry);

brkTable *dbFindBrkTable(DBBASE *pdbbase,char *name);

dbMenu *dbFindMenu(DBBASE *pdbbase,char *name);
char **dbGetChoices(DBENTRY *pdbentry);
int  dbGetMenuIndex(DBENTRY *pdbentry);
long dbPutMenuIndex(DBENTRY *pdbentry,int index);
int  dbGetNMenuChoices(DBENTRY *pdbentry);

int  dbAllocForm(DBENTRY *pdbentry);
long  dbFreeForm(DBENTRY *pdbentry);
char  **dbGetFormPrompt(DBENTRY *pdbentry);
char  **dbGetFormValue(DBENTRY *pdbentry);
long  dbPutForm(DBENTRY *pdbentry,char **value);
char  **dbVerifyForm(DBENTRY *pdbentry,char **value);

int  dbGetNLinks(DBENTRY *pdbentry);
long dbGetLinkField(DBENTRY *pdbentry,int index);
int  dbGetLinkType(DBENTRY *pdbentry);
long dbCvtLinkToConstant(DBENTRY *pdbentry);
long dbCvtLinkToPvlink(DBENTRY *pdbentry);

/*dump routines*/
void dbDumpPath(DBBASE *pdbbase);
void dbDumpRecord(DBBASE *pdbbase,char *precdesname,int level);
void dbDumpMenu(DBBASE *pdbbase,char *menuName);
void dbDumpRecDes(DBBASE *pdbbase,char *recdesName);
void dbDumpFldDes(DBBASE *pdbbase,char *recdesName,char *fname);
void dbDumpDevice(DBBASE *pdbbase,char *recdesName);
void dbDumpDriver(DBBASE *pdbbase);
void dbDumpBreaktable(DBBASE *pdbbase,char *name);
void dbPvdDump(DBBASE *pdbbase,int verbose);
void dbReportDeviceConfig(DBBASE *pdbbase,FILE *report);

/* Misc useful routines*/
/*general purpose allocation routines to invoke calloc and maloc	*/
/* NOTE: These routines do NOT return if they fail.			*/
void *dbCalloc(size_t nobj,size_t size);
void *dbMalloc(size_t size);

extern int dbStaticDebug;

#define S_dbLib_recdesNotFound (M_dbLib| 1)	/*Record Type does not exist*/
#define S_dbLib_recExists (M_dbLib| 3)		/*Record Already exists*/
#define S_dbLib_recNotFound (M_dbLib| 5)	/*Record Not Found*/
#define S_dbLib_flddesNotFound (M_dbLib| 7)	/*Field Description Not Found*/
#define S_dbLib_fieldNotFound (M_dbLib| 9)	/*Field Not Found*/
#define S_dbLib_badField (M_dbLib|11)		/*Bad Field value*/
#define S_dbLib_menuNotFound (M_dbLib|13)	/*Menu not found*/
#define S_dbLib_badLink (M_dbLib|15)		/*Bad Link Field*/
#define S_dbLib_nameLength (M_dbLib|17)		/*Record Name is too long*/
#define S_dbLib_noRecSup (M_dbLib|19)		/*Record support not found*/
#define S_dbLib_strLen (M_dbLib|21)		/*String is too long*/
#endif /*INCdbStaticLibh*/
