Program CharLessOrEqualProgram;
Var a, b : Char;

Begin

  writeln('''A'' <= ''A'': ', 'A' <= 'A');
  writeln('''A'' <= ''B'': ', 'A' <= 'B');
  writeln('''B'' <= ''A'': ', 'B' <= 'A');
  a := 'd';
  b := 'f';
  writeln('a: ', a, ' b: ', b, ' a <= b: ', a <= b);
  writeln('b: ', b, ' a: ', a, ' b <= a: ', b <= a);
  a := b;
  writeln('a: ', a, ' b: ', b, ' a <= b: ', a <= b);

End.
