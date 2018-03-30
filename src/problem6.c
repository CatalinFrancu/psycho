#include <stdio.h>
#include <mem.h>

typedef int Huge[85];
Huge A,B,C,C2,HTemp;
int N,k;

void Atrib(Huge H, int V)
/* H <- V */
{
  memset(H,0,sizeof(Huge));
  H[0]=1;
  H[1]=V;
}

void Add(Huge A, Huge B)
/* A <- A+B */
{ int i,T=0;

  if (B[0]>A[0])
    { for (i=A[0]+1;i<=B[0];) A[i++]=0;
      A[0]=B[0];
    }
    else for (i=B[0]+1;i<=A[0];) B[i++]=0;
  for (i=1;i<=A[0];i++)
    { A[i]+=B[i]+T;
      T=A[i]/10;
      A[i]%=10;
    }
  if (T) A[++A[0]]=T;
}

void WriteHuge(Huge H)
{ int i;

  for (i=H[0];i;printf("%d",H[i--]));
  printf("\n");
}

void main(void)
{
  printf("N=");scanf("%d",&N);
  Atrib(A,1);
  Atrib(B,0);
  Atrib(C,1);
  Atrib(C2,0);
  for (k=2;k<=N;k++)
    { memmove(HTemp,C,sizeof(Huge));
      Add(A,B);Add(A,B);  /* A(k) = A(k-1) + 2*B(k-1) */
      Add(B,C);           /* B(k) = B(k-1) + C(k-1)   */
      memmove(C,A,sizeof(Huge));
      Add(C,C2);          /* C(k) = A(k) + C(k-2)     */
      memmove(C2,HTemp,sizeof(Huge)); /* noul C(K-2) */
    }
  Add(B,B);               /* Rezultatul este 2*B(n)   */
  WriteHuge(B);
}
