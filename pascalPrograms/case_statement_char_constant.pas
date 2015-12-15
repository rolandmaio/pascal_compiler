Program CaseStatementCharConstantProgram;
Var a : Char;

Begin

  for a := 'A' to 'C' do
  Begin
    Case a of
      'A': writeln('A is for apple!')
      'B': writeln('B is for banana!')
      'C': writeln('C is for cookie!')
    End
  End;

End.
