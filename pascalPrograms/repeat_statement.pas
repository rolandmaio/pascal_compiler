Program RepeatStatementProgram;
Var sum, i, n : Integer;

Begin

  n := 100;
  sum := 0;
  i := 1;
  repeat
    begin
      if i MOD 10 = 0 then
        writeln('i: ', i);
      sum := sum + i;
      i := i + 1;
    end;
  until n < i;

  writeln('The sum of the first ', n, ' integers is ', sum);

End.
