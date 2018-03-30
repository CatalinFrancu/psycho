#include <stdio.h>
#include <stdlib.h>
#define Unknown 0xFFFF
#define Root 0xFFFE

typedef huge unsigned Vector[40320];
typedef char CharVector[40320];
typedef int Perm[8];
typedef struct list { unsigned X; struct list * Next; } List;

Perm StartPerm={1,2,3,4,5,6,7,8}, EndPerm;
const Perm Moves[3]=
   {{7,6,5,4,3,2,1,0},
    {3,0,1,2,5,6,7,4},
    {0,6,1,3,4,2,5,7}};
/* Cele trei tipuri de mutari */
Vector Father; /* Legaturile de tip tata */
CharVector MoveKind;
unsigned StartValue,EndValue;
/* Valorile atasate configuratiilor initiala si finala */
List *Head, *Tail; /* Coada de expandat */

/**** Bijectia care asociaza un numar unei permutari ****/

unsigned Perm2Int(Perm P)
{ int i,j,k,Fact=5040;
  unsigned Sum=0;

  for (i=0;i<=6;i++)
    { k=P[i]-1;
      for (j=0;j<i;j++)
        if (P[j]<P[i]) k--;
      Sum+=k*Fact;
      Fact/=(7-i);
    }
  return Sum;
}

void Int2Perm(unsigned Sum, Perm P)
{ int i,j,k,Order,Fact=5040;
  Perm Used={0,0,0,0,0,0,0,0};

  for (i=0;i<=7;i++)
    { Order=Sum/Fact;
      j=-1;
      for (k=0;k<=Order;k++)
        do j++; while (Used[j]);
      Used[j]=1;
      P[i]=j+1;
      Sum%=Fact;
      if (i!=7) Fact/=(7-i);
    }
}

/**** Lucrul cu liste ****/

void InitList(void)
{
  Head=Tail=malloc(sizeof(List));
  Tail->X=StartValue;
  Tail->Next=NULL;
}

void AddToTail(unsigned K)
{
  Tail->Next=malloc(sizeof(List));
  Tail=Tail->Next;
  Tail->X=K;
  Tail->Next=NULL;
}

void Behead(void)
/* Sterge capul listei */
{ List *LCor=Head;

  Head=Head->Next;
  free(LCor);
}

/**** Cautarea propriu-zisa ****/

void MakeMove(Perm P,Perm Q,int Kind)
/* Kind = 0, 1 sau 2 */
{ int i;
  for (i=0;i<=7;i++)
    Q[i]=P[Moves[Kind][i]];
}

void Expand(void)
{ List *LCor;
  Perm P1,P2;
  unsigned i,XSon,Done;

  InitList();
  do {
    Int2Perm(Head->X,P1);
    for(i=0;i<=2;i++)
      { MakeMove(P1,P2,i);
        XSon=Perm2Int(P2);
        if (Father[XSon]==Unknown)
          { Father[XSon]=Head->X;
            MoveKind[XSon]=i+65;
            AddToTail(XSon);
          }
      }
    Done=(Head->X==EndValue);
    Behead(); }
  while (!Done);
}

/* Intrarea si iesirea */

void InitData(void)
{ FILE *F=fopen("input.txt","rt");
  unsigned i;

  for (i=0;i<=7;i++) fscanf(F,"%d",&EndPerm[i]);
  fclose(F);
  StartValue=Perm2Int(StartPerm);
  EndValue=Perm2Int(EndPerm);
  for (i=0;i<40320;) Father[i++]=Unknown;
  Father[StartValue]=Root;
}

void WriteMove(FILE *F,unsigned K,int Len)
{
  if (K!=StartValue)
    { WriteMove(F,Father[K],Len+1);
      fprintf(F,"%c\n",MoveKind[K]);
    }
    else fprintf(F,"%d\n",Len);
}

void Restore(void)
{ FILE *F=fopen("output.txt","wt");

  WriteMove(F,EndValue,0);
  fclose(F);
}

void main(void)
{
  InitData();
  Expand();
  Restore();
}
