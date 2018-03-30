program VPV;
type Vector=array[1..400] of Integer;
     Matrix=array[1..400] of ^Vector;
var A:Matrix;
    i:Integer;

begin
  for i:=1 to 400 do New(A[i]);
  A[1]^[1]:=1;
  for i:=2 to 100 do A[i]^[i]:=A[i-1]^[i-1]+i;
  WriteLn(A[100]^[100]);
end.
