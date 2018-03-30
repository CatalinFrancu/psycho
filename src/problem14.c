#include <stdio.h>
#define NMax 101
#define Impossible -30000

int M[NMax], R[NMax][NMax], N;
void ReadData(void)
{ FILE *F = fopen("input.txt", "rt");
  int i;

  fscanf(F, "%d\n", &N);
  for (i=1; i<=N; fscanf(F, "%d", &M[i++]));
  fclose(F);
}

void Share(void)
{ int i,j;

  R[0][0]=0;
  for (i=1; i<N; R[0][i++]=Impossible);

  for (i=1; i<=N; i++)
    {
      for (j=0; j<N; j++)
        R[i][j] = R[i-1][j];
      for (j=0; j<N; j++)
        if (R[i-1][j] != Impossible
           && R[i-1][j] + M[N+1-i] > 
              R[i][ (R[i-1][j]+M[N+1-i]) % N ])
         R[i][ (R[i-1][j]+M[N+1-i]) % N ] =
         R[i-1][j] + M[N+1-i];
    }
}

void WriteSolution(void)
{ FILE *F = fopen("output.txt", "wt");
  int i,j;

  fprintf(F, "%d\n", R[N][0]);
  j=0;
  for (i=N; i; i--)
    if (R[i][j] != R[i-1][j])
      {
        fprintf(F, "%d ", N+1-i);
        j = (j + N - M[N+1-i]%N) % N;
      }
  fprintf(F, "\n");
  fclose(F);
}

void main(void)
{
  ReadData();
  Share();
  WriteSolution();
}
