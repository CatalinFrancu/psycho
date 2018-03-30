program Fragment;
type FragType=array[0..399,0..63] of Integer;
     Matrix=array[0..6] of ^FragType;
var B:Matrix;
    i:Integer;

function GetValue(i,j:Integer):Integer;
begin
  GetValue:=B[j shr 6]^[i,j and 63];
end;

procedure SetValue(i,j,Value:Integer);
begin
  B[j shr 6]^[i,j and 63]:=Value;
end;

begin
  for i:=0 to 6 do New(B[i]);
  SetValue(1,1,1);
  for i:=2 to 100 do SetValue(i,i,GetValue(i-1,i-1)+i);
  WriteLn(GetValue(100,100));
end.
