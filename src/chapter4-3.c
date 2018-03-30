#include <stdio.h>
#include <stdlib.h>
#define M 1000 // numarul de "intrari"
typedef struct _List {
          long P;
          struct _List * Next;
        } List;
typedef List * Hash[M];
Hash H;

void InitHash2(Hash H)
{ int i;

  for (i=0; i<M; H[i++]=NULL);
}

int h2(int K)
{
  return K%M;
}

int Search2(Hash H, int K)
/* Intoarce 0 daca elementul nu exista in hash
   sau 1 daca el exista */
{ List *L;

  for (L=H[h2(K)]; L && (L->P != K); L = L->Next);
  return L!=NULL;
}

void Add2(Hash H, int K)
{ List *L = malloc(sizeof(List));
  L->P = K;
  L->Next = H[h2(K)];
  H[h2(K)] = L;
}
