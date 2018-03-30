#include <stdio.h>
#include <math.h>
#define NMax 101
#define Infinity 30000
typedef int Matrix[NMax][NMax+1];

Matrix Alt, Eff;
int M, N;
FILE *OutF;

void ReadData(void)
{ FILE *F=fopen("input.txt", "rt");
  int i,j;

  fscanf(F, "%d %d\n", &M, &N);
  for (i=1; i<=M; i++)
    for (j=1; j<=N; j++)
      fscanf(F, "%d", &Alt[i][j]);
  fclose(F);
}

void Optimize(int X1, int Y1, int X2, int Y2)
/* Testeaza daca in (X1,Y1) se poate ajunge
   cu efort mai mic dinspre (X2,Y2) */
{
  if (Eff[X2][Y2]+abs(Alt[X1][Y1]-Alt[X2][Y2])<Eff[X1][Y1])
    Eff[X1][Y1]=Eff[X2][Y2]+abs(Alt[X1][Y1]-Alt[X2][Y2]);
}

void Traverse(void)
{ int i,j;

  for (j=1; j<=N;) Eff[1][j++]=0;
  for (i=1; i<=M; i++)
    Eff[i][0]=Eff[i][N+1]=Infinity; /* Bordeaza matricea */
  for (i=2; i<=M; i++)
    {
      for (j=1; j<=N; j++)
        {
          Eff[i][j]=Infinity;
          Optimize(i, j, i-1, j);       /* De la N  */
          Optimize(i, j, i-1, j-1);     /* De la NV */
          Optimize(i, j, i-1, j+1);     /* De la NE */
          Optimize(i, j, i, j-1);       /* De la V  */
        }
      for (j=N; j; j--)
        Optimize(i, j, i, j+1);         /* De la E  */
    }
}

void GoBack(int X, int Y)
/* Reconstituie drumul */
{
  if (X>1)
    if (Eff[X][Y]==Eff[X][Y-1]
                   +abs(Alt[X][Y-1]-Alt[X][Y]))
    GoBack(X, Y-1);
    else if (Eff[X][Y]==Eff[X-1][Y-1]
                        +abs(Alt[X-1][Y-1]-Alt[X][Y]))
    GoBack(X-1, Y-1);
    else if (Eff[X][Y]==Eff[X-1][Y]
                        +abs(Alt[X-1][Y]-Alt[X][Y]))
    GoBack(X-1, Y);
    else if (Eff[X][Y]==Eff[X-1][Y+1]
                        +abs(Alt[X-1][Y+1]-Alt[X][Y]))
    GoBack(X-1, Y+1);
    else if (Eff[X][Y]==Eff[X][Y+1]
                        +abs(Alt[X][Y+1]-Alt[X][Y]))
    GoBack(X, Y+1);
  if (X>1) fprintf(OutF, "->");
  fprintf(OutF,"(%d,%d)", X, Y);
}

void WriteSolution(void)
{ int j,k;

  OutF=fopen("output.txt", "wt");
  /* Cauta punctul de sosire */
  fputs("(a)\n",OutF);
  for (j=2, k=1; j<=N; j++)
    if (Eff[M][j]<Eff[M][k]) k=j;
  fprintf(OutF, "%d\n", Eff[M][k]);
  fputs("TRASEU: ",OutF);
  GoBack(M, k);
  fprintf(OutF,"\n");
  fclose(OutF);
}

void main(void)
{
  ReadData();
  Traverse();
  WriteSolution();
}
