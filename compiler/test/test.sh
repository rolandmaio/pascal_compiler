g++ testLexer.cpp ../src/lexer/lexer.cpp ../src/lexer/lexer.h ../src/token/token.h ../src/token/tag.h ../src/token/token.cpp -std=c++11 -o testLexer.exe && ./testLexer.exe
g++ notimplementederrortest.cpp -lm /usr/lib/x86_64-linux-gnu/libboost*\.so -o notimplementederrortest.exe -std=c++11 && ./notimplementederrortest.exe
g++ parsetreeloggerexceptiontest.cpp -lm /usr/lib/x86_64-linux-gnu/libboost*\.so -o parsetreeloggerexceptiontest.exe -std=c++11 && ./parsetreeloggerexceptiontest.exe
