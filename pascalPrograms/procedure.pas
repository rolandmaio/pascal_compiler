Program ProcedureProgram;

Var i : Integer;

Procedure IncrementPassByValue(x : Integer);
Begin
  writeln('Entering Procedure IncrementPassByValue');
  writeln('Value of x passed: ', x);
  x := x + 1;
  writeln('Incremented value of x: ', x);
  writeln('Exiting Procedure IncrementPassByValue');
End;

Procedure IncrementPassByReference(var x : Integer);
Begin
  writeln('Entering Procedure IncrementPassByReference');
  writeln('Value of x passed: ', x);
  x := x + 1;
  writeln('Incremented value of x: ', x);
  writeln('Exiting Procedure IncrementPassByReference');
End;


Begin
  writeln('Executing ProcedureProgram.');
  i := 10;
  writeln('i prior: ', i);
  writeln('Invoking IncrementPassByValue');
  IncrementPassByValue(i);
  writeln('i after: ', i);
  writeln();
  writeln('i prior: ', i);
  writeln('Invoking IncrementPassByReference');
  IncrementPassByReference(i);
  writeln('i after: ', i);
End.
