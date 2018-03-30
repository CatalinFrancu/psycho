#include <stdio.h>
#define NMax 5001
typedef unsigned IntVector[NMax];
typedef long LongVector[NMax];

IntVector T, R;
LongVector T1, T2;
int N;
FILE *OutF;

void ReadData(void)
{ FILE *F=fopen("input.txt", "rt");
  int i;

  fscanf(F,"%d\n", &N);
  for (i=1; i<=N;)
    fscanf(F,"%d", &T[i++]);
  for (i=1; i<N;)
    fscanf(F,"%d", &R[i++]);
}

long Min(long X, long Y)
{
  return X<Y? X : Y;
}
void Match(void)
{ int i;
  T1[1]=T[1]; T2[1]=0xFFFF; /* =Infinit */
  T1[2]=T[1]+T[2]; T2[2]=R[1];
  for (i=3; i<=N; i++)
    {
      T1[i]=T[i]+Min(T1[i-1],T2[i-1]);
      T2[i]=R[i-1]+Min(T1[i-2],T2[i-2]);
    }
}

void GoBack(int K)
{
  if (K)
    if (T1[K]<T2[K])
      { GoBack(K-1);
        fprintf(OutF,"%d\n",K);
      }
      else { GoBack(K-2);
             fprintf(OutF,"%d+%d\n",K-1,K);
           }
}

void WriteSolution(void)
{
  OutF=fopen("output.txt", "wt");
  fprintf(OutF,"%d\n",Min(T1[N],T2[N]));
  GoBack(N);
  fclose(OutF);
}

void main(void)
{
  ReadData();
  Match();
  WriteSolution();
}
