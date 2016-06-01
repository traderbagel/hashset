#include "hashset.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct hashset {
  char **table;
  size_t bits;
  size_t mask;
  size_t size;
  size_t capacity;
};

hashset_p hashset_create()
{
  hashset_p hs = (hashset_p) malloc( sizeof(hashset) );
  hs->bits = 2;
  hs->capacity = 1 << hs->bits;
  hs->mask = (1 << hs->bits) - 1;
  hs->size = 0;
  hs->table = (char **) calloc( hs->capacity, sizeof(char *));
  return hs;
}

void hashset_destroy(hashset_p hs)
{
  if (hs->table)
    free(hs->table);
}

unsigned char hashset_empty(hashset_p hs) 
{
  return hs->size == 0 ? 1 : 0 ;
}
/* djb2 */
unsigned long hash1(char *str)
{
  unsigned long hash = 5381;
  int c ;
  while( *str ) {
    c = *str;
    ++str;
    hash = ( (hash << 5) + hash ) + c; /* hash = hash * 33 + c */
  } 
  return hash;
}
/* sdbm */
unsigned long hash2(char *str)
{
  unsigned long hash = 0;
  int c;
  while ( *str) {
    c = *str;
    ++str;
    hash = c + ( hash << 6 ) + ( hash << 16 ) - hash; /*hash = hash * 65599 + c */
  }
  return hash;
}

unsigned char hashset_insert(hashset_p hs, char *str) 
{
  if ( !str || strlen(str) < 1 )
    return 0;
  
  int hash = hs->mask & hash1(str);  
  int c = 0;
  while ( !(hs->table[hash] == NULL) ) { //|| !(hs->table[hash] == -1) ) {
    if ( !strcmp( hs->table[hash], str ) )
      return 0;
    else 
      hash = hs->mask & ( hash + hash2(str) );
    if ( ++c > hs->capacity ) {
      assert("Bad Hash\n");
      return 0;
    }
  }
  ++hs->size;
  hs->table[hash] = strdup(str);
  return 1; 
}

unsigned char hashset_find(hashset_p hs, char *str)
{
  if ( !str || strlen(str) < 1 )
    return 0;
  int hash =  hs->mask & hash1(str);
  int c = 0;
  while( strcmp( hs->table[hash], str) ){
    hash = hs->mask & (hash + hash2(str) );
    if ( ++c > hs->capacity ) {
      assert("Bad Hash in Find \n");
      return 0;  
    }
  }
  return 1;
}
