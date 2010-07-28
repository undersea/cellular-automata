#ifdef __cplusplus
#include <cstdio>
#include <cstring>
#else
#include <stdio.h>
#include <string.h>
#endif

int cells[2][10][10];

int main(void)
{
  int i,j,k;
  bzero(cells, sizeof(cells));
  for(i=0;i<2;i++) {
    for(j=0;j<10;j++) {
      for(k=0;k<10;k++) {
	printf("%d\t", cells[i][k][j]);
      }
      putchar('\n');
    }
    putchar('\n');
  }

  return 0;
}

