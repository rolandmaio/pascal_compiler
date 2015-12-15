Program CaseStatementCharConstantProgram;
Var a : Char;

Begin

  for a := 'A' to 'F' do
  Begin
    Case a of
      'A', 'D': writeln('A is for apple or D is for dog!')
      'B', 'E': writeln('B is for banana or E is for elephant!')
      'C', 'F': writeln('C is for cookie or F is for fox!')
    End
  End;

End.
