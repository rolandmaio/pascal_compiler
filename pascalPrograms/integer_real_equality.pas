Program IntegerRealEqualityProgram;
Var x : Integer; y : Real;

Begin

  writeln('3 = 5.0: ', 3 = 5.0);
  writeln('4 = 4.0: ', 4 = 4.0);
  x := 0;
  y := 10.0;
  writeln('x: ', x, ' y: ', y, ' x = y: ', x = y);
  writeln('y: ', y, ' x: ', x, ' y = x: ', y = x);
  y := x;
  writeln('x: ', x, ' y: ', y, ' x = y: ', x = y);
  writeln('y: ', y, ' x: ', x, ' y = x: ', y = x);

End.
