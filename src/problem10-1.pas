program Invert;
const NMax=30;
      PMax=23;
var i,P:Integer;

function Invers(P,K:Integer):Integer;
var i:Integer;
begin
  i:=0;
  repeat Inc(i) until (K*i) mod P=1;
  Invers:=i;
end;

begin
  Assign(Output,'invers.txt');Rewrite(Output);
  for P:=2 to PMax do
    begin
      Write('{',P:2,'} (');
      for i:=1 to NMax do
        begin
          if (P in [2,3,5,7,11,13,17,19,23]) and (i<P)
            then Write(Invers(P,i):2)
            else Write(99);
          if i<>NMax then Write(',');
          if i=NMax div 2 then Write(#13#10'      ');
        end;
      WriteLn('),');
    end;
  Close(Output);
end.
