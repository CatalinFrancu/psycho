program Magic;
{$B-,I-,R-,S-}
{ Tabla este 1 2 3 4
             A B C D }
const r12='BCBBB'; { Roteste in sens orar coloanele 12 }
      r23='C';     { Roteste in sens orar coloanele 23 }
      r34='BBBCB'; { Roteste in sens orar coloanele 34 }
      r14='BBCBB'; { Roteste in sens orar coloanele 41 }

      plBCD=r12+r23+r34+r14; { Permuta patratele BCD }
      PL234=plBCD+'A'+plBCD+'A'; { Permuta coloanele 234 }

      { SXY schimba intre ele coloanele X si Y }
      S14='B'+PL234;
      S12='BBB'+S14+'B';
      S23='BB'+S14+'BB';
      S34='B'+S14+'BBB';
      S13=r12+r12+r23+r23+r12+r12;
      S24='B'+S13+'BBB';

      { RevXY schimba intre ele patratele vecine X si Y }
      RevC3=plBCD+r23+r12+r12+r34+r34+'BBB'+plBCD+'A';
      RevD4='BBB'+RevC3+'B';
      RevB2='B'+RevC3+'BBB';
      RevA1='BB'+RevC3+'BB';

      Rev23='C'+RevC3+'CCC';
      Rev12='B'+Rev23+'BBB';
      Rev34='BBB'+Rev23+'B';
      Rev14='BB'+Rev23+'BB';

      RevAB='A'+Rev12+'A';
      RevBC='A'+Rev23+'A';
      RevCD='A'+Rev34+'A';
      RevAD='A'+Rev14+'A';

type Matrix=array[1..2,1..4] of Integer;
     Vector=array[1..60000] of Char;
var A,B:Matrix;
    V:Vector;
    N:Integer;

procedure MakeAMatrix;
begin
  A[1,1]:=1;
  A[1,2]:=2;
  A[1,3]:=3;
  A[1,4]:=4;
  A[2,1]:=8;
  A[2,2]:=7;
  A[2,3]:=6;
  A[2,4]:=5;
end;

procedure ReadBMatrix;
begin
  Assign(Input,'input.txt');
  Reset(Input);
  Read(B[1,1]);
  Read(B[1,2]);
  Read(B[1,3]);
  Read(B[1,4]);
  Read(B[2,4]);
  Read(B[2,3]);
  Read(B[2,2]);
  Read(B[2,1]);
  Close(Input);
end;

procedure AddString(S:String);
{ Adauga o secventa la sirul-solutie }
var i:Integer;
begin
  for i:=1 to Length(S) do
    begin
      Inc(N);
      V[N]:=S[i];
    end;
end;

procedure FindElement(K:Integer;var X,Y:Integer);
{ Cauta un element intr-o permutare }
var i,j:Integer;
begin
  for i:=1 to 2 do
    for j:=1 to 4 do
      if A[i,j]=K then begin
                         X:=i;
                         Y:=j;
                         Exit;
                       end;
end;

procedure Switch(var X,Y:Integer);
{ Schimba intre ele doua numere }
var IAux:Integer;
begin
  IAux:=X;X:=Y;Y:=IAux;
end;

procedure Process;
{ Transforma pozitia in pozitia B prin schimbari
  repetate ale elementelor vecine }
var i,j,k,l,m:Integer;
begin
  for j:=1 to 4 do
    for i:=1 to 2 do
      begin
        FindElement(B[i,j],k,l);
        { Gaseste elementul care trebuie adus
          pe pozitia (i,j) }
        if k<>i then begin
                       { Il aduce pe linia corecta }
                       case l of
                         1:AddString(RevA1);
                         2:AddString(RevB2);
                         3:AddString(RevC3);
                         4:AddString(RevD4);
                       end; {case}
                       Switch(A[k,l],A[i,l]);
                       k:=i;
                     end;
        for m:=l downto j+1 do
          { Il aduce pe coloana corecta }
          begin
            if k=1
              then case m of
                     2:AddString(Rev12);
                     3:AddString(Rev23);
                     4:AddString(Rev34);
                   end
              else case m of
                     2:AddString(RevAB);
                     3:AddString(RevBC);
                     4:AddString(RevCD);
                   end;
            Switch(A[k,m],A[k,m-1]);
          end;
      end;
end;

procedure Cut(K,D:Integer);
{ Taie din vectorul V D pozitii incepand cu K }
var i:Integer;
begin
  for i:=K to N-D do
    V[i]:=V[i+D];
  Dec(N,D);
end;

procedure Reduce;
{ Reduce secventele de mutari identice }
var i:Integer;
begin
  i:=1;
  repeat
    case V[i] of
      'A':if (i<=N-1) and (V[i+1]='A')
            then Cut(i,2)
            else Inc(i);
      'B':if (i<=N-3) and (V[i+1]='B')
            and (V[i+2]='B') and (V[i+3]='B')
            then Cut(i,4)
            else Inc(i);
      'C':if (i<=N-3) and (V[i+1]='C')
            and (V[i+2]='C') and (V[i+3]='C')
            then Cut(i,4)
            else Inc(i);
    end; {case}
  until i=N;
end;

procedure WriteSolution;
var i:Integer;
begin
  Assign(Output,'output.txt');
  Rewrite(Output);
  WriteLn(N);
  for i:=1 to N do WriteLn(V[i]);
  Close(Output);
end;

begin
  N:=0;
  MakeAMatrix;
  ReadBMatrix;
  Process;
  Reduce;
  WriteSolution;
end.
