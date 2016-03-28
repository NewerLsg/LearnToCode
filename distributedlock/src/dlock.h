#ifndef DLOCK_H
#define DLOCK_H

int getLock(char* name);

int releaseLock(char* name);

int testLock(char* name);

#endif
