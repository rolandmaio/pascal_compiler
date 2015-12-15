Program CaseOfProgram;
Var n : Integer; message : String;

Begin

  for n := 0 to 2 do
    Begin
      Case n of
        0: Begin writeln('It''s a boy!'); writeln('At least I think so...'); End
        1: writeln('It''s a girl!')
        2: writeln('It''s undecided!')
      End
    End;

End.
