program ArrayProgram;
Var A: Array[1..10] of Integer;
    i: Integer;

begin

  for i := 1 to 10 do
    A[i] := i*i;

  for i := 1 to 10 do
    write(A[i], ' ');

  writeln;

end.
