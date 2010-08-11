#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(void)
{
  size_t al = 3664748294;
  char *ptr = NULL;
  al+=1000;
  while(ptr == NULL) {
    ptr = (char *)malloc(sizeof(char)*al);
    if(ptr == NULL) {
      //perror("could not assign memory");
      al -= 1;
      //al /= 2;
    }
  }
  printf("Max bytes that can be allocated are %lu +/- 10\n", al);
  printf("SIZE_MAX is %lu\n", SIZE_MAX);
  return 0;
}
