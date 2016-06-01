#include <stdio.h>
#include "hashset.h"

int main() 
{
  char *bar = "Hello World";
  char *foo = "Night Night";
  
  hashset_p hs = hashset_create();
  
  printf("Insert \"%s\", get return %d\n", bar, hashset_insert(hs,bar));
  printf("Find \"%s\", get return %d\n", foo, hashset_find(hs, foo));
  printf("Find \"%s\", get return %d\n", bar, hashset_find(hs, bar));
}
