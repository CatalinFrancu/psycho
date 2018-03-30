#include <stdio.h>
#define NMax 10002
typedef int Vector[NMax];

Vector V,Apar;
int N;

void ReadData(void)
{ int i;
  FILE *InF=fopen("input.txt","rt");

  fscanf(InF,"%d",&N);
  for (i=1;i<=N+2;Apar[i++]=0);
  for (i=1;i<=N;i++)
    { fscanf(InF,"%d",&V[i]);
      Apar[V[i]]++;
    }
  fclose(InF);
}

void Decode(void)
{ int Current=0,Next,i;
  FILE *OutF=fopen("output.txt","wt");

  do; while (Apar[++Current]);    /* Se cauta prima frunza */
  Next=Current;
  for (i=1;i<=N;i++)
    { fprintf(OutF,"%d %d\n",Current,V[i]);
      if (Current==Next) do; while (Apar[++Next]);
      /* Daca am ajuns la ultimul 0, mai caut unul */
      Apar[V[i]]--;
      Current=(V[i]<Next) && (Apar[V[i]]==0) ? V[i] : Next;
      /* Daca exista o frunza mai mica decat Next, */
      /* ea este prioritara, altfel revin la Next */
    }
  fprintf(OutF,"%d %d\n",Current,Next);
  fclose(OutF);
}

void main(void)
{
  ReadData();
  Decode();
}
