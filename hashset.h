#ifndef HASHSET_HASHSET_H
#define HASHSET_HASHSET_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hashset* hashset_p;

hashset_p hashset_create();

unsigned char hashset_empty(hashset_p );

unsigned char hashset_insert(hashset_p, char *);

unsigned char hashset_find(hashset_p, char *);

// unsigned char hashset_erase(hashset_p, int);

void hashset_destroy(hashset_p);


#ifdef __cplusplus
}
#endif

#endif 
