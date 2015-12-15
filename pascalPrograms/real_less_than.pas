Program RealLessThanProgram;
Var x, y : Real;

Begin

  writeln('3.4 < 5.8: ', 3.4 < 5.8);
  writeln('4.0 < 2.3: ', 4.0 < 2.3);
  x := 0.0;
  y := 10.0;
  writeln('x: ', x, ' y: ', y, ' x < y: ', x < y);
  x := y;
  writeln('x: ', x, ' y: ', y, ' x < y: ', x < y);

End.
