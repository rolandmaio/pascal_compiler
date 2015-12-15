Program RealEqualityProgram;
Var x, y : Real;

Begin

  writeln('3.2 = 5.2: ', 3.2 = 5.2);
  writeln('4.6 = 4.6: ', 4.6 = 4.6);
  x := 0.3;
  y := 10.9;
  writeln('x: ', x, ' y: ', y, ' x = y: ', x = y);
  x := y;
  writeln('x: ', x, ' y: ', y, ' x = y: ', x = y);

End.
