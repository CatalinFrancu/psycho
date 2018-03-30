#include <stdio.h>
typedef int Matrix[9][9];
typedef int Vector[9];
const Matrix A=
  {{3,3,3,3,3,2,3,2,0},  // Mutarile care misca ceasul C11
   {2,3,2,3,2,3,1,0,1},  // .
   {3,3,3,2,3,3,0,2,3},  // .
   {2,3,1,3,2,0,2,3,1},  // .
   {2,3,2,3,1,3,2,3,2},  // .
   {1,3,2,0,2,3,1,3,2},  // .
   {3,2,0,3,3,2,3,3,3},  // .
   {1,0,1,3,2,3,2,3,2},  // .
   {0,2,3,2,3,3,3,3,3}}; // Mutarile care misca ceasul C33

void main(void)
{ FILE *F=fopen("input.txt","rt");
  Vector V={0,0,0,0,0,0,0,0,0}; // Vectorul suma
  int i,j,k;

  for (i=0;i<=8;i++)
    { fscanf(F,"%d",&k);
      for (j=0;j<=8;j++)
        V[j]=(V[j]+(4-k)*A[i][j])%4;
    }
  fclose(F);

  F=fopen("output.txt","wt");
  for(i=0;i<=8;i++)
    for(j=1;j<=V[i];j++)
      fprintf(F,"%d ",i+1);
  fclose(F);
}

