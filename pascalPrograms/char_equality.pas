Program CharEqualitbProgram;
Var a, b : Char;

Begin

  writeln('''A'' = ''A'': ', 'A' = 'A');
  writeln('''A'' = ''B'': ', 'A' = 'B');
  a := 'd';
  b := 'f';
  writeln('a: ', a, ' b: ', b, ' a = b: ', a = b);
  a := b;
  writeln('a: ', a, ' b: ', b, ' a = b: ', a = b);

End.
