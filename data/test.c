#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(void)
{
  size_t al = 3202412494;
  char *ptr = NULL;

  al *= 10;
  while(ptr == NULL) {
    ptr = (char *)malloc(sizeof(char)*al);
    if(ptr == NULL) {
      //perror("could not assign memory");
      al -= 100000;
    }
  }
  printf("Max bytes that can be allocated are %lu +/- 10\n", al);
  printf("SIZE_MAX is %lu\n", SIZE_MAX);
  return 0;
}
