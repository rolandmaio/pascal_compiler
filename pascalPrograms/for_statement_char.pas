Program ForStatementCharProgram;
Var a : Char;

Begin

  for a := 'a' to 'z' do
    Begin
      write(a);
      if a < 'z' then
        write(' ');
      else
        writeln;
    End;

  for a := 'Z' downto 'A' do
    Begin
      write(a);
      if a > 'A' then
        write(' ');
      else
        writeln;
    End;

End.
