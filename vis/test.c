#include <stdio.h>

int main(void) {
  char a[100], b[100];
  int c, k;

  printf("Enter a: "); fflush(stdout);
  k = 0;
  while ((k < 100) && ((c = getchar()) != EOF)) {
    a[k++] = c;
  }
  a[k] = 0;

  //clearerr(stdin);

  printf("Enter b: "); fflush(stdout);
  k = 0;
  while ((k < 100) && ((c = getchar()) != EOF)) {
    b[k++] = c;
  }
  b[k] = 0;

  printf("a is [%s]; b is [%s]\n", a, b);
  return 0;
}