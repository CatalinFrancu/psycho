#include <stdio.h>

void main(void)
{ FILE *F=fopen("input.txt","rt");
  int SEven,SOdd,N,i,K;

  fscanf(F,"%d\n",&N);
  for (i=1, SEven=SOdd=0; i<=N; i++)
    { fscanf(F, "%d\n", &K);
      if (i&1) SOdd+=K;
        else SEven+=K;
    }
  fclose(F);

  printf("Mutarea mea: %c\n", SEven>=SOdd ? 'R' : 'L');
  for (i=1; i<N/2; i++)
    { printf("Mutarea dvs. (L/R) ? ");
      printf("Mutarea mea: %c\n", getchar());
      getchar(); /* Caracterul newline */
    }
  printf("Mutarea dvs. (L/R) ? ");
  getchar();

  if (SEven>=SOdd)
    printf("%d %d\n", SEven, SOdd);
    else printf("%d %d\n", SOdd, SEven);
}
