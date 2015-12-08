rm test_outfile.eml
bash build.sh
./compile.exe $1 && ./emulate.exe test_outfile.eml
