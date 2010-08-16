#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(void)
{
<<<<<<< HEAD
  size_t al = 3664748294;
  char *ptr = NULL;
  al+=1000;
=======
  size_t al = 3202412494;
  char *ptr = NULL;

  al *= 10;
>>>>>>> 6b67ca744299baa2db0d08c94a8e831c5c067d1a
  while(ptr == NULL) {
    ptr = (char *)malloc(sizeof(char)*al);
    if(ptr == NULL) {
      //perror("could not assign memory");
<<<<<<< HEAD
      al -= 1;
      //al /= 2;
=======
      al -= 100000;
>>>>>>> 6b67ca744299baa2db0d08c94a8e831c5c067d1a
    }
  }
  printf("Max bytes that can be allocated are %lu +/- 10\n", al);
  printf("SIZE_MAX is %lu\n", SIZE_MAX);
  return 0;
}
