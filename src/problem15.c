#include <stdio.h>
#define NMax 10000
#define None -1

int X[NMax], L[NMax], P, Q;

void ReadData(void)
{ FILE *F = fopen("input.txt", "rt");
  int i;

  fscanf(F, "%d %d\n", &P, &Q);
  for (i=1; i<P; fscanf(F, "%d", &X[i++]));
  fclose(F);
}

void FindSum(void)
{ long S=0;
  FILE *F = fopen("output.txt", "wt");
  int i,j;

  for (i=1, L[0]=0; i<P; L[i++] = None);
  i=0;
  while ( L[ (S+=X[++i]) % P ]==None && // Restul 0
          L[ (S%P+P-Q) % P ]==None )    // Restul Q
    L[S%P]=i;
  for (j = 1 + ((L[S%P]!=None)? L[S%P]: L[ (S%P+P-Q) % P ]);
       j <= i; fprintf(F, "%d ", j++));
  fclose(F);
}

void main(void)
{
  ReadData();
  FindSum();
}
