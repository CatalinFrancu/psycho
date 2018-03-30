#include <stdio.h>
#include <mem.h>
int V[10001], H[10001], N, K;

void ReadData(void)
{ FILE *F=fopen("input.txt","rt");
  int i;

  fscanf(F,"%d %d\n",&N, &K);
  for (i=1; i<=N; fscanf(F, "%d", &V[i++]));
  fclose(F);
}

void Sift(int X, int N)
/* Cerne al X-lea element dintr-un heap de N elemente */
{ int Son;

  /* Alege un fiu mai mare ca tatal */
  if (X<<1<=N)
    { Son=X<<1;
      if (X<<1<N && H[(X<<1)+1]<H[(X<<1)])
        Son++;
      if (H[Son]>=H[X]) Son=0;
    }
    else Son=0;
  while (Son)
    { /* Schimba H[X] cu H[Son] */
      H[X]=(H[X]^H[Son])^(H[Son]=H[X]);
      X=Son;
      /* Alege un alt fiu */
      if (X<<1<=N)
        { Son=X<<1;
          if (X<<1<N && H[(X<<1)+1]<H[(X<<1)])
            Son++;
          if (H[Son]>=H[X]) Son=0;
        }
        else Son=0;
    }
}

void SortVector(void)
{ int i;

  /* Construieste heap-ul de K+1 elemente */
  for (i=1; i<=K+1; H[i++]=V[i]);
  for (i=(K+1) >> 1; i; Sift(i--, K+1));

  for (i=1; i<=N; i++)
    { V[i] = H[1]; // minimul trece in vector
      /* Se adauga un element din vector sau din heap */
      H[1] = (i<=N-K-1) ? V[i+K+1] : H[K+1];
      /* Daca vectorul s-a terminat, heap-ul incepe
         sa se micsoreze */
      if (i>N-K-1) K--;
      /* Cerne noul element */
      Sift(1, K+1);
    }
}

void WriteSolution(void)
{ FILE *F=fopen("con","wt");
  int i;

  for (i=1; i<=N; fprintf(F, "%d ", V[i++]));
  fprintf(F, "\n");
  fclose(F);
}

void main(void)
{
  ReadData();
  SortVector();
  WriteSolution();
}
