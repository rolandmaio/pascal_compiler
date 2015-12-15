Program ProcedureProgram;

Var i : Integer;

Procedure Meow(z : Integer);
Begin
  writeln('Meow! z ', z);
End;

Procedure Bark(y : Integer);
Begin
  writeln('Woof! y ', y);
  Meow(20);
End;

Procedure IncrementPassByValue(x : Integer);
Begin
  writeln('Entering Procedure IncrementPassByValue');
  writeln('Value of x passed: ', x);
  x := x + 1;
  writeln('Incremented value of x: ', x);
  Bark(15);
  writeln('Exiting Procedure IncrementPassByValue');
End;

Begin
  writeln('Executing ProcedureProgram.');
  i := 10;
  writeln('i prior: ', i);
  writeln('Invoking IncrementPassByValue');
  IncrementPassByValue(i);
  writeln('i after: ', i);
End.
