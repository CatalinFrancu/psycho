#include <stdio.h>
int G[10001], N;
long Sum;
FILE *OutF;

void ReadData(void)
{ FILE *F=fopen("input.txt","rt");
  int i;

  fscanf(F,"%d\n",&N);
  for (i=1, Sum=0; i<=N; i++)
    { fscanf(F,"%d",&G[i]);
      Sum+=G[i];
    }
  fclose(F);
}

void Sift(int K, int N)
/* Cerne al K-lea element dintr-un heap de N elemente */
{ int Son;

  /* Alege un fiu mai mare ca tatal */
  if (K<<1<=N)
    { Son=K<<1;
      if (K<<1<N && G[(K<<1)+1]>G[(K<<1)])
        Son++;
      if (G[Son]<=G[K]) Son=0;
    }
    else Son=0;
  while (Son)
    { /* Schimba G[K] cu G[Son] */
      G[K]=(G[K]^G[Son])^(G[Son]=G[K]);
      K=Son;
      /* Alege un alt fiu */
      if (K<<1<=N)
        { Son=K<<1;
          if (K<<1<N && G[(K<<1)+1]>G[(K<<1)])
            Son++;
          if (G[Son]<=G[K]) Son=0;
        }
        else Son=0;
    }
}

void HeapSort(void)
{ int i;

  /* Construieste heap-ul */
  for (i=N>>1; i;) Sift(i--,N);
  /* Sorteaza vectorul */
  for (i=N; i>=2;)
    { G[1]=(G[1]^G[i])^(G[i]=G[1]);
      Sift(1,--i);
    }
}

void Match(void)
{ int i, First=1;

  while (G[First]==1 && First<N) First++;
  /* Trebuie adaugata si conditia First<N
     pentru a acoperi cazul particular N=2 */
  for (i=1; i<=N-2; i++)
    { fprintf(OutF,"%d %d\n", i, First);
      First+=(--G[First]==1);
    }
  fprintf(OutF,"%d %d\n", N-1, N);
}

void main(void)
{
  ReadData();
  OutF=fopen("output.txt","wt");
  if (Sum==(N-1)<<1)
    { HeapSort();
      Match();
    }
    else fputs("Problema nu are solutie!\n",OutF);
  fclose(OutF);
}
