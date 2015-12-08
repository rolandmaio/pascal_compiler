Program GotoStatementProgram;
Label label1, label2;
Var sum, i, j, n, goal : Integer;

Begin

  n := 100;
  goal := 12350;

  for i := 0 to n do
    for j := 0 to n do
      if i*i + j*j = goal then
        Begin
          writeln(i, '*', i, ' + ', j, '*', j, ' = ', n);
          goto label1;
        End;

  writeln('There do not exist integers i, j that satisfy the equation i*i + j*j = ', goal);
  label1:

  goal := 20000;

  for i := 0 to n do
    for j := 0 to n do
      if i*i + j*j = goal then
        Begin
          writeln(i, '*', i, ' + ', j, '*', j, ' = ', goal);
          goto label2;
        End;

  writeln('There do not exist integers i, j i,j in [0, 100] that satisfy the equation i*i + j*j = ', goal);
  label2:

End.
