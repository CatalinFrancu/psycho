#include <stdio.h>
#define NMax 5000
float V[NMax+1], Lo[NMax+1], Hi[NMax+1];
float Delta, Max, Min;
int N;

void ReadData(void)
/* Citeste vectorul si afla maximul si minimul */
{ FILE *F=fopen("input.txt", "rt");
  int i;

  fscanf(F, "%d\n", &N);
  fscanf(F, "%f", &V[1]);
  Max=Min=V[1];

  for (i=2; i<=N; i++)
    {
      fscanf(F, "%f", &V[i]);
      if (V[i]>Max) Max=V[i];
        else if (V[i]<Min) Min=V[i];
    }
  fclose(F);
}

void Split(void)
{ int i, K;

  Delta = (Max-Min)/(N-1);
  /* Se initializeaza vectorii Lo si Hi */
  for (i=0; i<=N; Lo[i]=Max+1, Hi[i++]=Min-1);

  /* Se construiesc intervalele */
  for (i=1; i<=N; i++)
    {
      K = (V[i]-Min)/Delta;
      if (V[i]<Lo[K]) Lo[K]=V[i];
      if (V[i]>Hi[K]) Hi[K]=V[i];
    }
}

void Rebuild(void)
/* Rescrie vectorul V, pentru a economisi memorie,
   pastrand numai capetele intervalelor */
{ int i, M=0;

  for (i=0;i<N; i++)
    {
      if (Lo[i] != Max+1) V[++M]=Lo[i];
      if (Hi[i] != Min-1 && Hi[i] != Lo[i]) V[++M]=Hi[i];
    }
  N=M;
}

void FindGap(void)
/* Acum cautarea distantei maxime se face
   secvential, vectorul fiind sortat */
{ int i;
  float Gap=0;

  for (i=2; i<=N; i++)
    if (V[i]-V[i-1] > Gap)
      Gap = V[i]-V[i-1];
  printf("Distanta maxima este %0.3f\n", Gap);
}

void main(void)
{
  ReadData();
  if (Max==Min)
    puts("0");
  else
    {
      Split();
      Rebuild();
      FindGap();
    }
}
