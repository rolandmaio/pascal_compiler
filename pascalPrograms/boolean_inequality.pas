Program BooleanInequalityProgram;
Var a, b : Boolean;

Begin
  writeln('True <> True: ', True <> True);
  writeln('False <> True: ', False <> True);
  writeln('True <> False: ', True <> False);
  writeln('False <> False: ', False <> False);
  a := True;
  b := True;
  writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b);
  a := True;
  b := False;
  writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b);
  a := False;
  b := True;
  writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b);
  a := False;
  b := False;
  writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b);
End.
