Program BooleanVarProgram;
Var a, b : Boolean;

Begin
  a := True;
  b := False;
  writeln('a is: ', a);
  writeln('And b is: ', b);
  a := b;
  writeln('but now a is: ', a, ' and b is: ', b);
End.
