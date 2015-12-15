Program CaseOfProgram;
Var n : Integer; message : String;

Begin

  for n := 0 to 5 do
    Begin
      Case n of
        0, 3: Begin writeln('It''s a boy!'); writeln('At least I think so...'); End
        1, 4: writeln('It''s a girl!')
        2, 5: writeln('It''s undecided!')
      End
    End;

End.
