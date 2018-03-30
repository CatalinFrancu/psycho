program LongestPrefix;
{$B-,D-,I-,R-,S-}
const NMax=100;
      LMax=20;
type Str20=String[LMax+1];
     LexType=array[1..NMax] of Str20;
     BooleanVector=array[1..LMax+1] of Boolean;
     BufferType=array[1..62000] of Byte;
var Lex:LexType;     { Dictionarul de primitive }
    N:Integer;       { Numarul de primitive }
    Biggest:LongInt; { Lungimea maxima }
    Buf:BufferType;  { Buffer de intrare }

procedure ReadPrimitives;
var i,Len:Integer;
begin
  Assign(Input,'input.txt');
  Reset(Input);
  ReadLn(N);
  for i:=1 to N do
    begin
      ReadLn(Len);
      ReadLn(Lex[i]);
    end;
  Close(Input);
end;

procedure Decompose;
var Last:Str20;  { Ultimele 20 de caractere citite }
    CanGet:BooleanVector;
     { CanGet[i] indica daca Last[i] poate fi
       ultimul caracter al unei descompuneri }
    i,L:Integer;
    Current:LongInt; { Lungimea curenta }
begin
  Assign(Input,'data.txt');
  SetTextBuf(Input,Buf,SizeOf(Buf));
  Reset(Input);  { Deschide fisierul cu un buffer atasat }

  Biggest:=0;
  Last[0]:=Chr(LMax+1);
  FillChar(Last,LMax,'@');
  FillChar(CanGet,LMax,True);
  Current:=0;  { Deocamdata nu s-a citit nimic }

  ReadLn(Last[LMax+1]); { Citeste primul caracter }
  repeat
    Inc(Current);
    i:=0;
    { Cauta o primitiva potrivita }
    repeat
      Inc(i);
      L:=Length(Lex[i]);
      CanGet[LMax+1]:=CanGet[LMax+1-L]
        and (Copy(Last,LMax+2-L,L)=Lex[i]);
    until CanGet[LMax+1] or (i=N);
    { Am gasit o primitiva? }
    if CanGet[LMax+1]
      then Biggest:=Current;
    { Deplaseaza spre stanga CanGet si Last }
    Move(CanGet[2],CanGet[1],LMax);
    Move(Last[2],Last[1],LMax);
    { Avanseaza la urmatorul caracter }
    ReadLn(Last[LMax+1]);
  until Last[LMax+1]='.';

  Close(Input);
end;

procedure WriteSolution;
begin
  Assign(Output,'output.txt');
  Rewrite(Output);
  WriteLn(Biggest);
  Close(Output);
end;

begin
  ReadPrimitives;
  Decompose;
  WriteSolution;
end.
