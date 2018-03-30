#include <stdio.h>
#define NMax 10001

int V[NMax], /* Vectorul */
    T[NMax], /* Vectorul de tati */
    S[NMax], /* Stiva */
    N;       /* Numarul de elemente */

void ReadData(void)
{ FILE *F=fopen("input.txt","rt");
  int i;

  fscanf(F,"%d\n",&N);
  for (i=1; i<=N;)
    fscanf(F, "%d", &V[i++]);
}

void BuildTree(void)
{ int i,k,LenS=0;

  S[0]=0; /* Pentru ca initial T[1] sa fie 0 */
  for (i=1; i<=N; i++)
    { /* Cauta pozitia pe care va fi inserat V[i] */
      k=LenS+1;
      while (V[S[k-1]]>V[i]) k--;
      /* Face corecturile in S si T */
      T[i]=S[k-1];
      if (k<=LenS) T[S[k]]=i;
      /* i este ultimul element din stiva, deci... */
      S[LenS=k]=i;
    }
}

void WriteSolution(void)
{ FILE *F=fopen("output.txt","wt");
  int i;
  for (i=1; i<=N;)
    fprintf(F,"%d ",T[i++]);
  fprintf(F,"\n");
}

void main(void)
{
  ReadData();
  BuildTree();
  WriteSolution();
}
