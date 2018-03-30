program Hamilton;
{$B-,I-,R-,S-}
const NMax=30;
type Vector=array[1..NMax] of Integer;
     Matrix=array[1..NMax,1..NMax] of Integer;
var A:Matrix;
    Route,BestRoute:Vector;
    N,Cost,MinCost,i:Integer;

procedure ReadData;
var i,j:Integer;
begin
  Assign(Input,'input.txt');Reset(Input);
  ReadLn(N);
  for i:=1 to N do
    begin
      for j:=1 to N do Read(A[i,j]);
      ReadLn;
    end;
  Close(Input);
end;

procedure Greedy1(Start:Integer;var R:Vector;
                  var Cost:Integer);
var i,j,Closest:Integer;
    Seen:set of 1..NMax;
begin
  R[1]:=Start;
  Cost:=0;
  Seen:=[Start];
  for i:=2 to N do
    begin
      { Cauta nodul cel mai apropiat }
      Closest:=MaxInt;
      for j:=1 to N do
        if (not (j in Seen)) and (A[R[i-1],j]<Closest)
          then begin
                 Closest:=A[R[i-1],j];
                 R[i]:=j;
               end;
      Inc(Cost,Closest);
      Seen:=Seen+[R[i]];
    end;
  { Inchide ciclul }
  Inc(Cost,A[R[N],Start]);
end;

procedure Update;
begin
  if Cost<MinCost
    then begin
           MinCost:=Cost;
           BestRoute:=Route;
         end;
end;

procedure WriteSolution;
var i:Integer;
begin
  Assign(Output,'output.txt');Rewrite(Output);
  WriteLn(MinCost);
  for i:=1 to N do Write(BestRoute[i],' ');
  WriteLn;
  Close(Output);
end;

begin
  ReadData;
  MinCost:=MaxInt;
  for i:=1 to N do
    begin
      Greedy1(i,Route,Cost);
      Update;
    end;
  WriteSolution;
end.
