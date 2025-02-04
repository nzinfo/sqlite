#ifndef UNLOCK_NOTIFY_H
#define UNLOCK_NOTIFY_H

#include <sqlite3ext.h>

#ifdef _WIN32
#include <windows.h>
typedef struct {
    int fired;
    CONDITION_VARIABLE cond;
    CRITICAL_SECTION mu;
} _unlock_note;
#else
#include <pthread.h>
typedef struct {
    int fired;
    pthread_cond_t cond;
    pthread_mutex_t mu;
} _unlock_note;
#endif

_unlock_note* _unlock_note_alloc(void);
void _unlock_note_fire(_unlock_note* un);
void _unlock_note_free(_unlock_note* un);
int _wait_for_unlock_notify(sqlite3 *db, _unlock_note* un);

#endif /* UNLOCK_NOTIFY_H */