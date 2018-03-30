program Hamilton;
{$B-,I-,R-,S-}
const NMax=30;
      TimeLimit=30; { secunde }

type Vector=array[1..NMax] of Integer;
     Matrix=array[1..NMax,1..NMax] of Integer;
var A:Matrix;
    Route,BestRoute:Vector;
    Seen:set of 1..NMax;
    N,Cost,MinCost:Integer;
    Time:LongInt absolute $0000:$046C;
    Alarm:LongInt;

procedure SetAlarm;
begin
  Alarm:=Time+TimeLimit*17;
  { Cifra corecta era nu 17, ci 18.2;
    am pastrat insa o rezerva de siguranta }
end;

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

procedure RandomCycle;
var i,j:Integer;
begin
  Route[1]:=Random(N)+1;
  Seen:=[Route[1]];
  Cost:=0;
  for i:=2 to N do
    begin
      repeat Route[i]:=Random(N)+1;
      until not (Route[i] in Seen);
      Seen:=Seen+[Route[i]];
      Inc(Cost,A[Route[i-1],Route[i]]);
    end;
  Inc(Cost,A[Route[N],Route[1]]);
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
  SetAlarm;
  Randomize;
  ReadData;
  MinCost:=MaxInt;
  while Time<Alarm do
    begin
      RandomCycle;
      Update;
    end;
  WriteSolution;
end.
