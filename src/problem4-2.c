#include <stdio.h>
#include <stdlib.h>
#define NMax 101

int D[NMax][NMax], A[NMax], N;

void ReadData(void)
{ FILE *F=fopen("input.txt","rt");
  int i;

  fscanf(F,"%d\n",&N);
  for (i=1; i<=N;)
    fscanf(F, "%d\n", &A[i++]);
  fclose(F);
}

int Min(int A, int B)
{
  return A<B ? A : B;
}

int Max(int A, int B)
{
  return A>B ? A : B;
}

void FindMax(void)
{ int i,j,k;

  for (i=1;i<N;i++)
    D[i][i+1]=abs(A[i]-A[i+1]);
  for (k=3;k<=N-1;k++)
    for (i=1;i+k<=N;i++)
      { j=i+k;
        D[i][j]=Max(A[i]+Min(D[i+2][j]-A[i+1],
                             D[i+1][j-1]-A[j]),
                    A[j]+Min(D[i+1][j-1]-A[i],
                             D[i][j-2]-A[j-1]));
      }
  printf("Diferenta maxima este %d\n",D[1][N]);
}

void main(void)
{
  ReadData();
  FindMax();
}
