Program RealGreaterOrEqualProgram;
Var x, y : Real;

Begin

  writeln('3.0 >= 5.6: ', 3.0 >= 5.6);
  writeln('4.8 >= 2.2: ', 4.8 >= 2.2);
  writeln('18 >= 18: ', 18 >= 18);
  x := 0.0;
  y := 10.0;
  writeln('x: ', x, ' y: ', y, ' x >= y: ', x >= y);
  x := y;
  writeln('x: ', x, ' y: ', y, ' x >= y: ', x >= y);
  x := 20.5;
  writeln('x: ', x, ' y: ', y, ' x >= y: ', x >= y);

End.
