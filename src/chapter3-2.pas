program Nibbles;
type Vector=array[0..62499] of Byte;
var V:Vector;

function GetValue(X:LongInt):Word;
var Oct,Nib:Word;
begin
  Oct:=Pred(X) shr 1;
  Nib:=Pred(X) and 1;
  GetValue:=(V[Oct] and ($0F shl (Nib shl 2)))
            shr (Nib shl 2);
end;

procedure SetValue(X:LongInt;K:Word);
var Oct,Nib:Word;
begin
  Oct:=Pred(X) shr 1;
  Nib:=Pred(X) and 1;
  V[Oct]:=(V[Oct] and ($FF xor ($0F shl (Nib shl 2))))
          or (K shl (Nib shl 2));
end;

begin
  FillChar(V,SizeOf(V),0);
  SetValue(12345,12);
  SetValue(12346,13); { Doi nibble de pe acelasi octet }
  WriteLn(GetValue(12345),' ',GetValue(12346));
end.
