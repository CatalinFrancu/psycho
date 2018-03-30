#define M 9973 // numarul de "intrari"
typedef struct {
          char b_T[8][8];
            /* tabla de joc, cu 0<= T[i][j] <=12 */
          char b_CastleW, b_CastleB;
            /*  ultimii doi biti ai lui b_CastleW
                indica daca albul are dreptul de a
                efectua rocada mare, respectiv pe cea
                mica. Analog pentru b_CastleB */
          char b_Side;
            /* 0 sau 1, dupa cum la mutare este albul
               sau negrul */
          char b_EP;
            /* 0..8, indicand coloana (0..7) pe care
               partea la mutare poate efectua o
               captura "en passant". 8 indica ca nu
               exista aceasta posibilitate */
          int b_NMoves;
            /* Numarul de mutari efectuate */
        } Board;
Board B;

int h3(Board *B)
{ int i,j;
  /* Valoarea initiala a lui S este un numar pe 17 biti care
     inglobeaza toate variabilele suplimentare pe langa T.
     S se va lua apoi modulo M */
  long S = (B->b_NMoves           /* 8 biti */
          +(B->b_CastleW << 8)    /* 2 biti */
          +(B->b_CastleB << 10)   /* 2 biti */
          +(B->b_Side << 12)      /* 1 bit */
          +B->b_EP<<13) % M;      /* 4 biti */

  for (i=0; i<=7; i++)
    for (j=0; j<=7; j++)
      S=(16*S+B->b_T[i][j])%M;

  return S;
}
