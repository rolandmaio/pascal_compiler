Program ForStatementProgram;
Var sum, i, n : Integer;

Begin

  n := 1;
  sum := 0;
  for i := 1 to n do
    sum := sum + i;

  writeln('The sum of the first ', n, ' integers is ', sum);

End.
