Program IfStatementProgram;
Var x, y : Integer;

Begin

  x := 0;
  y := 10;
  if x <= y then writeln('x is less than or equal y');
  x := 2*y;
  if x <= y then
    writeln('x is less than or equal y');
  else
    writeln('x is not less than or equal y');

End.
