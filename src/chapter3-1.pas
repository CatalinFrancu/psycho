program VectorDeBiti;
type Vector=array[0..62499] of Byte;
var V:Vector;
    N,X,i:LongInt;

function GetValue(X:LongInt):Boolean;
begin
  GetValue:=V[Pred(X) shr 3] and (1 shl (Pred(X) and 7))<>0;
end;

procedure SetValue(X:LongInt;B:Boolean);
begin
  if B
    then V[Pred(X) shr 3]:=V[Pred(X) shr 3] or
                           (1 shl (Pred(X) and 7))
    else V[Pred(X) shr 3]:=V[Pred(X) shr 3] and
                           ($FF xor (1 shl (Pred(X) and 7)));
end;

begin
  FillChar(V,SizeOf(V),0);
  Assign(Input,'input.txt');Reset(Input);
  ReadLn(N);
  for i:=1 to N-1 do
    begin
      ReadLn(X);
      SetValue(X,True);
    end;
  Close(Input);
  i:=0;
  repeat Inc(i) until not GetValue(i);
  WriteLn(i);
end.
