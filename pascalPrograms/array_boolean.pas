program ArrayProgram;
Var A: Array[Boolean] of Integer;
    b: Boolean;

begin

  b := False;
  A[b] := 0;

  b := True;
  A[b] := 1;

  writeln(A[False], ' ', A[True]);

end.
