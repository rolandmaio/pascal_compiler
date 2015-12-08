Program CaseOfProgram;
Var n : Integer; message : String;

Begin

  for n := 0 to 2 do
    begin
      Case (n) of
        0: writeln('It''s a boy!');
        1: writeln('It''s a girl!');
        2: writeln('It''s undecided!');
      end;
    end;

End.
