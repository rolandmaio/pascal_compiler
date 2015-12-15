program ArrayProgram;
Var A: Array['a'..'z'] of Integer;
    c: Char;
    i: Integer;

begin

  i := 1;

  for c := 'a' to 'z' do
    Begin
      A[c] := i*i;
      i := i + 1;
    End;

  for c := 'a' to 'z' do
    Begin
      write(A[c]);
      if c < 'z' then
        write(' ');
      else
        writeln;
    End;

end.
