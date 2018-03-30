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

procedure Bkt(Level,Cost:Integer);
var i:Integer;
begin
  if Level=N+1
    then begin
           Inc(Cost,A[Route[N],1]);
           if Cost<MinCost
             then begin
                    BestRoute:=Route;
                    MinCost:=Cost;
                  end;
         end
    else if (Time<Alarm) and (Cost<MinCost)
           then for i:=1 to N do
             if not (i in Seen)
               then begin
                      Seen:=Seen+[i];
                      Route[Level]:=i;
                      Bkt(Level+1,Cost+A[Route[Level-1],i]);
                      Seen:=Seen-[i];
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
  ReadData;
  Route[1]:=1;
  Seen:=[1];
  MinCost:=MaxInt;
  Bkt(2,0);
  WriteSolution;
end.
