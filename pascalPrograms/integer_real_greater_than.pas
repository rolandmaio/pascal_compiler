Program IntegerRealGreaterThanProgram;
Var x : Integer; y : Real;

Begin

  writeln('3 > 5.0: ', 3 > 5.0);
  writeln('5 > 4.0: ', 5 > 4.0);
  x := 0;
  y := 10.0;
  writeln('x: ', x, ' y: ', y, ' x > y: ', x > y);
  writeln('y: ', y, ' x: ', x, ' y > x: ', y > x);
  y := x;
  writeln('x: ', x, ' y: ', y, ' x > y: ', x > y);
  writeln('y: ', y, ' x: ', x, ' y > x: ', y > x);

End.
