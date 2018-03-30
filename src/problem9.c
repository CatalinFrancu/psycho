#include <stdio.h>
#define NMax 1000
typedef long Vector[NMax+1];

Vector T,S,P,Q,F; /* T = Vectorul de tati,
                     S = sociabilitatile,
                     P,Q = caracteristicile,
                     F = numarul de fii */
int N,Root;

void InitData(void)
{ int i;
  FILE *InF=fopen("input.txt","rt");

  fscanf(InF,"%d",&N);
  for (i=1;i<=N+1;F[i++]=0);
  for (i=1;i<=N;i++)
    { fscanf(InF,"%d",&T[i]);
      if (T[i]) F[T[i]]++; else Root=i;
    }
  for (i=1;i<=N;i++) fscanf(InF,"%d",&S[i]);
  fclose(InF);

  for (i=1;i<=N;P[i++]=S[i]);
  for (i=1;i<=N;Q[i++]=0);
}

void FindNext(int *K,int *Next)
{ F[T[*K]]--;
  F[*K]=-1;
  if ((F[T[*K]]>0) || (T[*K]>*Next))
    { *K=*Next;
      while (F[*Next]) (*Next)++;
    }
    else *K=T[*K];
}

void TraverseTree(void)
{ int K=0,Next,i;

  do; while (F[++K]);
  Next=K; do; while (F[++Next]);
  for (i=1;i<N;i++)
    { P[T[K]]+=Q[K];
      Q[T[K]]+=(P[K]>Q[K]) ? P[K] : Q[K];
      FindNext(&K,&Next);
    }
}

void main(void)
{
  InitData();
  TraverseTree();
  printf("%ld\n",P[Root]);
}
