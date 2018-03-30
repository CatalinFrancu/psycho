#include <stdio.h>
#include <stdlib.h>
#define Infinity 30000
typedef int Vector[10001];

Vector V,P,Q,*S;
int N,Len; /* Len = Lungimea vectorului Q */

void ReadData(void)
{ FILE *F=fopen("input.txt","rt");
  int i;

  fscanf(F,"%d",&N);
  for(i=1;i<=N;i++) fscanf(F,"%d",&V[i]);
  fclose(F);
}

int Insert(int K,int Lo,int Hi)
{ int Mid=(Lo+Hi)/2;

  if (Lo==Hi)
    { if (Hi>Len) Q[++Len+1]=Infinity;
      Q[Lo]=K;
      return Lo;
    }
    else if (K<Q[Mid]) return Insert(K,Lo,Mid);
                     else return Insert(K,Mid+1,Hi);
}

void BuildPQ(void)
{ int i,Place;

  Len=0;Q[1]=Infinity;
  for (i=1;i<=N;i++)
    P[i]=Insert(V[i],1,Len+1);
}

void BuildS(void)
{ int i,K=N;

  S=malloc(sizeof(*S));
  for (i=Len;i;i--)
    { while (P[K]!=i) K--;
      (*S)[i]=V[K];
    }
}

void WriteSolution(void)
{ FILE *F=fopen("output.txt","wt");
  int i;

  fprintf(F,"%d\n",Len);
  for(i=1;i<=Len;i++) fprintf(F,"%d\n",(*S)[i]);

  fclose(F);
}

void main(void)
{
  ReadData();
  BuildPQ();
  BuildS();
  WriteSolution();
}
