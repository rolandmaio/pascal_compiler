Program ProcedurePassByReferenceProgram;

Var i : Integer;

Procedure IncrementPassByReference(var x : Integer);
Begin
  writeln('Entering Procedure IncrementPassByReference');
  writeln('Value of x passed: ', x);
  x := x + 1;
  writeln('Incremented value of x: ', x);
  writeln('Exiting Procedure IncrementPassByReference');
End;


Begin

  writeln('Executing ProcedurePassByReferenceProgram.');
  i := 10;
  writeln('i prior: ', i);
  writeln('Invoking IncrementPassByReference');
  IncrementPassByReference(i);
  writeln('i after: ', i);
End.
