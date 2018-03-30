#include <stdio.h>
#define NMax 200
unsigned char A[NMax+1][NMax+1];
int N,RealN;

void FindNextFree(int Line,int *K)
/* Cauta (circular) urmatorul spatiu liber pe linia Line */
{ do *K=*K%(N-1)+1;
  while (A[Line][*K]);
}

void MakeMatrix(void)
{ int i,j,k;

  for (i=1;i<=N;i++)
    for (j=1;j<=N;j++) A[i][j]=0;
  for (i=1;i<N;i++)  /* Pentru fiecare echipa */
    { if (i==1)      /* Alege coloana de start */
        j=1;
        else { j=0;
               do j++; while (A[i][j]!=i-1);
               FindNextFree(i,&j);
               FindNextFree(i,&j);
             }
      for (k=i+1;k<=N;k++) /* Completeaza circular linia */
        { A[i][j]=k;
          A[k][j]=i;
          if (k<N) FindNextFree(i,&j);
        }
    }
}

void WriteMatrix(void)
{ int i,j;
  FILE *F=fopen("output.txt","wt");

  for (i=1;i<=RealN;i++)
    { for (j=1;j<N;j++)
        fprintf(F,"%4d",A[i][j]>RealN ? 0 : A[i][j]);
      fprintf(F,"\n");
    }
  fclose(F);
}

void main(void)
{
  printf("N=");scanf("%d",&RealN);
  N=RealN+RealN%2; /* Se adauga 1 daca RealN e impar */
  MakeMatrix();
  WriteMatrix();
}
