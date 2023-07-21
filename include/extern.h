#ifndef __LIBEMPIRE_EXTERN__
#define __LIBEMPIRE_EXTERN__

#include <pthread.h>

/*
 * You MUST use this library at linking and runtime
 * -lpthread might be set after this library in LDFLAGS
 * Remember to set LD_LIBRARY_PATH.
 * None of thoses functions will do your job!
 * Thoses are entry points for the Referee.
 * mutex_id parameter of lempire_take_fork/lempire_release_fork functions
 * is the pointer of the (const) mutex you use to handle the current fork.
 */

/* MUST be the first instruction in your main to Init the library */
int RCFStartup(int ac, char **av);

/* MUST be called after use to release library ressources */
void RCFCleanup();

/* Call it when a roman is eating */
int lempire_eat();

/* Call it when a roman is sleeping */
int lempire_sleep();

/* Call it when a roman is thinking */
int lempire_think();

/* Call it when a roman takes a fork */
int lempire_take_fork(const pthread_mutex_t *mutex_id);

/* Call it when a roman releases a fork */
int lempire_release_fork(const pthread_mutex_t *mutex_id);

#endif /* __LIBEMPIRE_EXTERN__ */
