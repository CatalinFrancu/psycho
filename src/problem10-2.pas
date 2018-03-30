program ParaNT;
{$B-,I-,R-,S-}
const NMax=30;
      PMax=23;
      NoWay=0;
      OpNames:String[4]='+-*/';
      Invers:array[2..PMax,1..NMax] of Integer=
{ 2}(( 1,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 3} ( 1, 2,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 4} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 5} ( 1, 3, 2, 4,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 6} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 7} ( 1, 4, 5, 2, 3, 6,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 8} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{ 9} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{10} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{11} ( 1, 6, 4, 3, 9, 2, 8, 7, 5,10,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{12} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{13} ( 1, 7, 9,10, 8,11, 2, 5, 3, 4, 6,12,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{14} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{15} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{16} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{17} ( 1, 9, 6,13, 7, 3, 5,15, 2,12,14,10, 4,11, 8,
      16,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{18} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{19} ( 1,10,13, 5, 4,16,11,12,17, 2, 7, 8, 3,15,14,
       6, 9,18,99,99,99,99,99,99,99,99,99,99,99,99),
{20} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{21} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{22} (99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,
      99,99,99,99,99,99,99,99,99,99,99,99,99,99,99),
{23} ( 1,12, 8, 6,14, 4,10, 3,18, 7,21, 2,16, 5,20,
      13,19, 9,17,15,11,22,99,99,99,99,99,99,99,99));

type Matrix=array[1..NMax, 1..NMax, 0..PMax] of Integer;
       { S-a inclus si valoarea PMax, care nu poate fi
         atinsa, pentru a se depozita "deseurile" }
     Vector=array[1..NMax] of Integer;
var A:Matrix;       { Matricea de calcul }
    V:Vector;       { Numerele }
    N,P,D:Integer;

procedure ReadData;
var i:Integer;
begin
  Assign(Input,'input.txt');Reset(Input);
  ReadLn(P,N,D);
  for i:=1 to N do Read(V[i]);
  Close(Input);
end;

function Expr(X,Y,Op:Integer):Integer;
{ Calculeaza expresia (X Op Y) unde Op=1 ('+'),
  Op=2 ('-'), Op=3 ('*'), Op=4 ('/'). Daca Op=4
  si Y=0 se returneaza valoarea P (care nu poate
  fi atinsa prin alte operatii corecte). }
begin
  case Op of
    1:Expr:=(X+Y) mod P;
    2:Expr:=(X+P-Y) mod P;
    3:Expr:=(X*Y) mod P;
    4:if Y=0 then Expr:=P  { = imposibil }
             else Expr:=(X*Invers[P,Y]) mod P
      { S-a creat o tabela predefinita de inversi,
        deoarece altfel impartirea se efectua numai
        in O(P) }
  end; {case}
end;

procedure Combine(i,j,k:Integer);
{ Urmeaza a se combina toate valorile posibile
  pentru A[i,k] si A[k+1,j] pentru a se afla
  toate valorile posibile pentru A[i,j] }
var p1,p2,Op:Integer;
begin
  for p1:=0 to P-1 do
    if A[i,k,p1]<>NoWay
      then for p2:=0 to P-1 do
             if A[k+1,j,p2]<>NoWay
               then { Am gasit doua valori posibile
                      si aplicam cei patru operatori }
                    for Op:=1 to 4 do
                      A[i,j,Expr(p1,p2,Op)]:=k;
end;

procedure ComposeMatrix;
var i,j,k,l:Integer;
begin
  { Initializarea matricei }
  for i:=1 to N do
    for j:=1 to N do
      for k:=0 to P-1 do A[i,j,P]:=NoWay;

  for i:=1 to N do
    A[i,i,V[i]]:=1; { sau orice <> NoWay }

  for l:=2 to N do { Lungimea intervalelor }
    for i:=1 to N-l+1 do
      begin
        j:=i+l-1; { S-au fixat [i,j] capetele intervalului }
        for k:=i to j-1 do { Se alege locul de impartire }
          Combine(i,j,k);
      end;
end;

procedure SeekValues(Lo,Hi,Mid,Value:Integer;
                     var v1,v2:Integer; var Op:Char);
{ Se stie unde e "sparta" expresia in doua; se cauta
  valorile care trebuie obtinute pentru partea stanga,
  respectiv dreapta, si pentru operator }
var i,j,k:Integer;
begin
  for i:=0 to P-1 do
    if A[Lo,Mid,i]<>NoWay
      then for j:=0 to P-1 do
             if A[Mid+1,Hi,j]<>NoWay
               then for k:=1 to 4 do
                      if Expr(i,j,k)=Value
                        then begin
                               v1:=i;
                               v2:=j;
                               Op:=OpNames[k];
                               Exit;
                             end;
end;

procedure WriteExpression(Lo,Hi,Value:Integer);
var v1,v2,Place:Integer;
    Op:Char;
begin
  if Lo=Hi
    then Write(V[Lo])
    else begin
           Place:=A[Lo,Hi,Value];
           SeekValues(Lo,Hi,Place,Value,v1,v2,Op);
           Write('(');
           WriteExpression(Lo,Place,v1);
           Write(Op);
           WriteExpression(Place+1,Hi,v2);
           Write(')');
         end;
end;

procedure WriteSolution;
begin
  Assign(Output,'output.txt');Rewrite(Output);
  if A[1,N,D]=NoWay
    then Write('Nu exista solutie')
    else WriteExpression(1,N,D);
  WriteLn;
  Close(Output);
end;

begin
  ReadData;
  ComposeMatrix;
  WriteSolution;
end.
