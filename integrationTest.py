""" Program to execute compiler and emulator integration testing. """
import sys
import subprocess

tests = [('writeln test',
          '',
          'writeln(\'Hello, world!\');',
          'Unit test failed on writeln test',
          'Integration test failed on writeln test',
          'Hello, world!\n'
      ), ('integer addition test',
          '',
          'writeln(\'102 + 2 is: \', 102 + 2);',
          'Unit test failed on integer addition',
          'Integration test failed on integer addition',
          '102 + 2 is: 104\n'
      ), ('integer multiplication test',
          '',
          'writeln(\'56 * 73 is: \', 56 * 73);',
          'Unit test failed on integer multiplication',
          'Integration test failed on integer multiplication',
          '56 * 73 is: 4088\n'
      ), ('integer division test',
          '',
          "writeln('10 DIV 3 is: ', 10 DIV 3);writeln('15 div 5 is: ', 15 div 5);writeln('20 div 21 is: ', 20 DIV 21);",
          'Unit test failed on integer division',
          'Integration test failed on integer division',
          '10 DIV 3 is: 3\n15 div 5 is: 3\n20 div 21 is: 0\n'
      ), ('integer subtraction test',
          '',
          "writeln('10 - 3 is: ', 10 - 3);writeln('15 - 5 is: ', 15 - 5);writeln('20 - 21 is: ', 20 - 21);",
          'Unit test failed on integer subtraction',
          'Integration test failed on integer subtraction',
          '10 - 3 is: 7\n15 - 5 is: 10\n20 - 21 is: -1\n'
      ), ('write real test',
          '',
          "writeln(2.0);",
          'Unit test failed on write real',
          'Integration test failed on write real',
          '2.000000\n'
      ), ('real addition test',
          '',
          "writeln(2.0 + 2.0);",
          'Unit test failed on real addition',
          'Integration test failed on real addition',
          '4.000000\n'
      ), ('real multiplication test',
          '',
          "writeln(2.7 * 10.0);",
          'Unit test failed on real multiplication',
          'Integration test failed on real multiplication',
          '27.000000\n'
      ), ('real division test',
          '',
          'writeln(10.0 / 2.5);',
          'Unit test failed on real division',
          'Integration test failed on real division',
          '4.000000\n'
      ), ('real subtraction test',
          '',
          'writeln(1022.0 - 652.0);',
          'Unit test failed on real subtraction',
          'Integration test failed on real subtraction',
          '370.000000\n'
      ), ('integer real addition test',
          '',
          'writeln(45.5 + 2);writeln(2 + 2.0);',
          'Unit test failed on integer real addition test',
          'Integration test failed on integer real addition test',
          '47.500000\n4.000000\n'
      ), ('integer real subtraction test',
          '',
          'writeln(45.5 - 2);writeln(21 - 2.0);',
          'Unit test failed on integer real subtraction test',
          'Integration test failed on integer real subtraction test',
          '43.500000\n19.000000\n'
      ), ('integer real multiplication test',
          '',
          'writeln(45.5 * 2);writeln(2 * 2.2);',
          'Unit test failed on integer real multiplication test',
          'Integration test failed on integer real multiplication test',
          '91.000000\n4.400000\n'
      ), ('integer real division test',
          '',
          'writeln(10 / 3); writeln(45.5 / 2); writeln(2 / 2.2);',
          'Unit test failed on integer real division test',
          'Integration test failed on integer real division test',
          '3.333333\n22.750000\n0.909091\n'
      ), ('integer mod test',
          '',
          "writeln('10 MOD 3 is: ', 10 MOD 3); writeln('15 mod 5 is: ', 15 mod 5); writeln('20 mod 21 is: ', 20 MOD 21);",
          'Unit test failed on integer mod test',
          'Integration test failed on integer mod test',
          '10 MOD 3 is: 1\n15 mod 5 is: 0\n20 mod 21 is: 20\n'
      ), ('write test',
          '',
          "write ('Hello, world.');",
          'Unit test failed on write test',
          'Integration test failed on write test',
          'Hello, world.'
      ), ('string var test',
          'Var str : String;',
          "str := 'Hello, string world!'; writeln(str);",
          'Unit test failed on string var test',
          'Integration test failed on string var test',
          'Hello, string world!\n'
      ),
         ('string var 2 test',
          'Var str1, str2 : String;',
          "str1 := 'This is str1';str2 := 'And this is str2'; writeln(str1, ' ', str2);",
          'Unit test failed on string var 2 test',
          'Integration test failed on string var 2 test',
          'This is str1 And this is str2\n'
      ), ('int var test',
          'Var x, y : Integer;',
          "x := 2; y := 2; writeln('x + y = ', x + y); x := 3; y := x; writeln('x + y = ', x + y);",
          'Unit test failed on int var test',
          'Integration test failed on int var test',
          'x + y = 4\nx + y = 6\n'
      ), ('real var test',
          'Var x, y : Real;',
          "x := 2.5; y := 1.5; writeln('x + y = ', x + y); x := 7.25; y := x; writeln('x + y = ', x + y);",
          'Unit test failed on real var test',
          'Integration test failed on real var test',
          'x + y = 4.000000\nx + y = 14.500000\n'
      ), ('write boolean literal test',
          '',
          "writeln('True is: ', True); writeln('And False is: ', False);",
          'Unit test failed on write boolean literal test',
          'Integration test failed on write boolean literal test',
          'True is: True\nAnd False is: False\n'
      ), ('boolean var test',
          "Var a, b : Boolean;",
          "a := True; b := False; writeln('a is: ', a); writeln('And b is: ', b); a := b; writeln('but now a is: ', a, ' and b is: ', b);",
          'Unit test failed on boolean variable test',
          'Integration test failed on boolean variable test',
          'a is: True\nAnd b is: False\nbut now a is: False and b is: False\n'
      ), ('boolean equality test',
          "Var a, b : Boolean;",
          "writeln('True = True: ', True = True); writeln('False = True: ', False = True); writeln('True = False: ', True = False); writeln('False = False: ', False = False); a := True; b := True; writeln('a: ', a, ' b: ', b, ' a = b: ', a = b); a := True; b := False; writeln('a: ', a, ' b: ', b, ' a = b: ', a = b); a := False; b := True; writeln('a: ', a, ' b: ', b, ' a = b: ', a = b); a := False; b := False; writeln('a: ', a, ' b: ', b, ' a = b: ', a = b);",
          'Unit test failed on boolean equality test',
          'Integration test failed on boolean equality test',
          'True = True: True\nFalse = True: False\nTrue = False: False\nFalse = False: True\na: True b: True a = b: True\na: True b: False a = b: False\na: False b: True a = b: False\na: False b: False a = b: True\n'
      ), ('boolean inequality test',
          'Var a, b : Boolean;',
          "writeln('True <> True: ', True <> True); writeln('False <> True: ', False <> True); writeln('True <> False: ', True <> False); writeln('False <> False: ', False <> False); a := True; b := True; writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b); a := True; b := False; writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b); a := False; b := True; writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b); a := False; b := False; writeln('a: ', a, ' b: ', b, ' a <> b: ', a <> b);",
          'Unit test failed on boolean inequality test',
          'Integration test failed on boolean inequality test',
          'True <> True: False\nFalse <> True: True\nTrue <> False: True\nFalse <> False: False\na: True b: True a <> b: False\na: True b: False a <> b: True\na: False b: True a <> b: True\na: False b: False a <> b: False\n'
      ), ('integer equality test',
          'Var x, y : Integer;',
          "writeln('3 = 5: ', 3 = 5); writeln('4 = 4: ', 4 = 4); x := 0; y := 10; writeln('x: ', x, ' y: ', y, ' x = y: ', x = y); x := y; writeln('x: ', x, ' y: ', y, ' x = y: ', x = y);",
          'Unit test failed on integer equality test',
          'Integration test failed on integer equality test',
          '3 = 5: False\n4 = 4: True\nx: 0 y: 10 x = y: False\nx: 10 y: 10 x = y: True\n'
      ), ('integer inequality test',
          'Var x, y : Integer;',
          "writeln('3 <> 5: ', 3 <> 5); writeln('4 <> 4: ', 4 <> 4); x := 0; y := 10; writeln('x: ', x, ' y: ', y, ' x <> y: ', x <> y); x := y; writeln('x: ', x, ' y: ', y, ' x <> y: ', x <> y);",
          'Unit test failed on integer inequality test',
          'Integer test failed on integer inequality test',
          '3 <> 5: True\n4 <> 4: False\nx: 0 y: 10 x <> y: True\nx: 10 y: 10 x <> y: False\n'
      ), ('integer less than test',
          'Var x, y : Integer;',
          "writeln('3 < 5: ', 3 < 5); writeln('4 < 2: ', 4 < 2); x := 0; y := 10; writeln('x: ', x, ' y: ', y, ' x < y: ', x < y); x := y; writeln('x: ', x, ' y: ', y, ' x < y: ', x < y);",
          'Unit test failed on integer less than test',
          'Integration test failed on integer less than test',
          '3 < 5: True\n4 < 2: False\nx: 0 y: 10 x < y: True\nx: 10 y: 10 x < y: False\n'
      ), ('integer greater than test',
          'Var x, y : Integer;',
          "writeln('3 > 5: ', 3 > 5); writeln('4 > 2: ', 4 > 2); x := 20; y := 10; writeln('x: ', x, ' y: ', y, ' x > y: ', x > y); x := y; writeln('x: ', x, ' y: ', y, ' x > y: ', x > y);",
          'Unit test failed on integer greater than test',
          'Integration test failed on intger greater than test',
          '3 > 5: False\n4 > 2: True\nx: 20 y: 10 x > y: True\nx: 10 y: 10 x > y: False\n'
      ), ('integer less or equal test',
          'Var x, y : Integer;',
          "writeln('3 <= 5: ', 3 <= 5); writeln('4 <= 2: ', 4 <= 2); writeln('18 <= 18: ', 18 <= 18); x := 0; y := 10; writeln('x: ', x, ' y: ', y, ' x <= y: ', x <= y); x := y; writeln('x: ', x, ' y: ', y, ' x <= y: ', x <= y); x := 20; writeln('x: ', x, ' y: ', y, ' x <= y: ', x <= y);",
          'Unit test failed on integer less or equal test',
          'Integration test failed on integer less or equal test',
          '3 <= 5: True\n4 <= 2: False\n18 <= 18: True\nx: 0 y: 10 x <= y: True\nx: 10 y: 10 x <= y: True\nx: 20 y: 10 x <= y: False\n'
      ), ('integer greater or equal test',
          'Var x, y : Integer;',
          "writeln('3 >= 5: ', 3 >= 5); writeln('4 >= 2: ', 4 >= 2); writeln('18 >= 18: ', 18 >= 18); x := 0; y := 10; writeln('x: ', x, ' y: ', y, ' x >= y: ', x >= y); x := y; writeln('x: ', x, ' y: ', y, ' x >= y: ', x >= y); x := 20; writeln('x: ', x, ' y: ', y, ' x >= y: ', x >= y);",
          'Unit test failed on integer greater or equal test',
          'Integration test failed on integer greater or equal test',
          '3 >= 5: False\n4 >= 2: True\n18 >= 18: True\nx: 0 y: 10 x >= y: False\nx: 10 y: 10 x >= y: True\nx: 20 y: 10 x >= y: True\n'
      ), ('if statement test',
          'Var x, y : Integer;',
          "x := 0; y := 10; if x <= y then writeln('x is less than or equal y'); x := 2*y; if x <= y then writeln('x is less than or equal y'); else writeln('x is not less than or equal y');",
          'Unit test failed on if statement test',
          'Integration test failed on if statement test',
          'x is less than or equal y\nx is not less than or equal y\n'
      ), ('for statement test',
          'Var sum, i, j, n : Integer;',
          "n := 100; sum := 0; for i := 1 to n do sum := sum + i; writeln('The sum of the first ', n, ' integers is ', sum); for i := 0 to n do for j := 0 to n do if i*i + j*j = n then writeln(i, '*', i, ' + ', j, '*', j, ' = ', n);",
          'Unit test failed on for statement test',
          'Integration test failed on for statement test',
          'The sum of the first 100 integers is 5050\n0*0 + 10*10 = 100\n6*6 + 8*8 = 100\n8*8 + 6*6 = 100\n10*10 + 0*0 = 100\n'
      ), ('goto statement test',
          'Label label1, label2;\nVar sum, i, j, n, goal : Integer;',
"  n := 100;\n\
  goal := 12350;\n\
\n\
  for i := 0 to n do\n\
    for j := 0 to n do\n\
      if i*i + j*j = goal then\n\
        Begin\n\
          writeln(i, '*', i, ' + ', j, '*', j, ' = ', n);\n\
          goto label1;\n\
        End;\n\
\n\
  writeln('There do not exist integers i, j that satisfy the equation i*i + j*j = ', goal);\n\
  label1:\n\
\n\
  goal := 20000;\n\
\n\
  for i := 0 to n do\n\
    for j := 0 to n do\n\
      if i*i + j*j = goal then\n\
        Begin\n\
          writeln(i, '*', i, ' + ', j, '*', j, ' = ', goal);\n\
          goto label2;\n\
        End;\n\
\n\
  writeln('There do not exist integers i, j i,j in [0, 100] that satisfy the equation i*i + j*j = ', goal);\n\
  label2:\n\
",
          'Unit test failed on goto test',
          'Integration test failed on goto test',
          'There do not exist integers i, j that satisfy the equation i*i + j*j = 12350\n100*100 + 100*100 = 20000\n'
      ), ('while statement test',
          'Var sum, i, n : Integer;',
          "n := 100; sum := 0; i := 1; while i < n do begin if i MOD 10 = 0 then writeln('i: ', i); sum := sum + i; i := i + 1; end; writeln('The sum of the first ', n - 1, ' integers is ', sum);",
          'Unit test failed on while statement test',
          'Integration test failed on while statement test',
          'i: 10\ni: 20\ni: 30\ni: 40\ni: 50\ni: 60\ni: 70\ni: 80\ni: 90\nThe sum of the first 99 integers is 4950\n'
      ), ('repeat statement test',
          'Var sum, i, n : Integer;',
          "n := 100; sum := 0; i := 1; repeat begin if i MOD 10 = 0 then writeln('i: ', i); sum := sum + i; i := i + 1; end; until n < i; writeln('The sum of the first ', n, ' integers is ', sum);",
          'Unit test failed on repeat statement test',
          'Integration test failed on repeat statement test',
          'i: 10\ni: 20\ni: 30\ni: 40\ni: 50\ni: 60\ni: 70\ni: 80\ni: 90\ni: 100\nThe sum of the first 100 integers is 5050\n'
      ), ('array test',
          'Var A: Array[1..10] of Integer; i: Integer;',
          "for i := 1 to 10 do A[i] := i*i; for i := 1 to 10 do write(A[i], ' '); writeln();",
          'Unit test failed on array test',
          'Integration test failed on array test',
          '1 4 9 16 25 36 49 64 81 100 \n'
      ), ('procedure pass by value no local variables test',
          "Var i : Integer; Procedure IncrementPassByValue(x : Integer); Begin writeln('Entering Procedure IncrementPassByValue'); writeln('Value of x passed: ', x); x := x + 1; writeln('Incremented value of x: ', x); writeln('Exiting Procedure IncrementPassByValue'); End;",
          "writeln('Executing ProcedureProgram.'); i := 10; writeln('i prior: ', i); writeln('Invoking IncrementPassByValue'); IncrementPassByValue(i); writeln('i after: ', i); writeln();",
          'Unit test failed on procedure pass by value no local variables test',
          'Integration test failed on procedure pass by value no local variables test',
          'Executing ProcedureProgram.\ni prior: 10\nInvoking IncrementPassByValue\nEntering Procedure IncrementPassByValue\nValue of x passed: 10\nIncremented value of x: 11\nExiting Procedure IncrementPassByValue\ni after: 10\n\n'
      )
]

programNameTemplate = 'program {programName};'

programTemplate = [
    'program {programName};',
    'begin',
    'end.'
]

def main():

    print('Building project')
    subprocess.call(
        ['bash', 'build.sh'],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL
    )

    print('Executing unit tests:')
    for test in tests:
        name, vardecl_code, body_code, unit_fmsg, intg_fmsg, expected = test
        print('\tTesting {name}:'.format(name=name), end="\t")
        programTemplate[0] = programNameTemplate.format(
            programName=name.replace(' ', '')
        )
        with open('compiler_unit_test.pas', 'w') as sourceFile:
            sourceFile.write(
                '\n'.join(
                    [programTemplate[0]] +\
                    [vardecl_code] +\
                    [programTemplate[1]] +\
                    [body_code] +\
                    programTemplate[2:]
                )
            )
        subprocess.call(
            ['./compile.exe', 'compiler_unit_test.pas'],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )
        with open('unit_test_output', 'w+') as testOutput:
            subprocess.call(
                ['./emulate.exe', 'test_outfile.eml'],
                stdout=testOutput
            )
            testOutput.seek(0)
            if testOutput.read() == expected:
                print('okay!')
            else:
                print(unit_fmsg)
                sys.exit(1)

    print('Unit testing complete')
    print('Integration testing has not yet been implemented')
    # The integration testing will be to execute all of the tests together in
    # the same program starting with the first 2, and iteratively adding
    # another test case if the test is successful and reporting the failure and
    # exiting otherwise.

if __name__ == '__main__':
    main()
