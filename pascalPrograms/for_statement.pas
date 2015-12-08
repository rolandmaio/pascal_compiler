Program ForStatementProgram;
Var sum, i, j, n : Integer;

Begin

  n := 100;
  sum := 0;
  for i := 1 to n do
    sum := sum + i;

  writeln('The sum of the first ', n, ' integers is ', sum);

  for i := 0 to n do
    for j := 0 to n do
      if i*i + j*j = n then writeln(i, '*', i, ' + ', j, '*', j, ' = ', n);

End.
