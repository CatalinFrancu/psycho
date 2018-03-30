#include <stdio.h>
int N;
FILE *OutF;

void Jump(int Level, char A, char B)
{ int i;
  putc(A,OutF);
  for (i=1;i<=Level;i++) putc(B,OutF);
  if (Level<N)
    {
      Jump(Level+1,'1'+'2'-A,'4'+'3'-B);
      for (i=1;i<=Level;i++) putc(B,OutF);
    }
  putc(A,OutF);
}

void main(void)
{
  printf("N=");scanf("%d",&N);
  OutF=fopen("output.txt","wt");
  fprintf(OutF,"%ld\n",(long)N*(N+2));
  Jump(1,'1','4');
  fprintf(OutF,"\n");
  fclose(OutF);
}
