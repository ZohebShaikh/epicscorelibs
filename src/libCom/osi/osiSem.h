#ifndef osiSemh
#define osiSemh

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "shareLib.h"

typedef void *semId;
typedef enum {semTakeOK,semTakeTimeout,semTakeError} semTakeStatus;
typedef enum {semEmpty,semFull} semInitialState;

epicsShareFunc semId epicsShareAPI semBinaryCreate(int initialState);
static INLINE semId semBinaryMustCreate (int initialState);
epicsShareFunc void epicsShareAPI semBinaryDestroy(semId id);
epicsShareFunc void epicsShareAPI semBinaryGive(semId id);
epicsShareFunc semTakeStatus epicsShareAPI semBinaryTake(semId id);
static INLINE void semBinaryMustTake (semId id);
epicsShareFunc semTakeStatus epicsShareAPI semBinaryTakeTimeout(semId id, double timeOut);
epicsShareFunc semTakeStatus epicsShareAPI semBinaryTakeNoWait(semId id);
epicsShareFunc void epicsShareAPI semBinaryShow(semId id);

epicsShareFunc semId epicsShareAPI semMutexCreate(void);
static INLINE semId semMutexMustCreate (void);
epicsShareFunc void epicsShareAPI semMutexDestroy(semId id);
epicsShareFunc void epicsShareAPI semMutexGive(semId id);
epicsShareFunc semTakeStatus epicsShareAPI semMutexTake(semId id);
static INLINE void semMutexMustTake(semId id);
epicsShareFunc semTakeStatus epicsShareAPI semMutexTakeTimeout(semId id, double timeOut);
epicsShareFunc semTakeStatus epicsShareAPI semMutexTakeNoWait(semId id);
epicsShareFunc void epicsShareAPI semMutexShow(semId id);

/*NOTES:
    Mutex semaphores MUST implement recursive locking
    Mutex semaphores should implement priority inheritance and deletion safe
*/

static INLINE semId semBinaryMustCreate (int initialState)
{
    semId id = semBinaryCreate (initialState);
    assert (id);
    return id;
}

static INLINE void semBinaryMustTake (semId id)
{
    assert (semBinaryTake (id)==semTakeOK);
}

static INLINE semId semMutexMustCreate (void)
{
    semId id = semMutexCreate ();
    assert (id);
    return id;
}

static INLINE void semMutexMustTake(semId id)
{
    assert (semMutexTake (id)==semTakeOK);
}


#ifdef __cplusplus
}
#endif


#endif /* osiSemh */
