Program IntegerLessOrEqualProgram;
Var x, y : Integer;

Begin

  writeln('3 <= 5: ', 3 <= 5);
  writeln('4 <= 2: ', 4 <= 2);
  writeln('18 <= 18: ', 18 <= 18);
  x := 0;
  y := 10;
  writeln('x: ', x, ' y: ', y, ' x <= y: ', x <= y);
  x := y;
  writeln('x: ', x, ' y: ', y, ' x <= y: ', x <= y);
  x := 20;
  writeln('x: ', x, ' y: ', y, ' x <= y: ', x <= y);

End.
