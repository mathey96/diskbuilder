emcc -o main.js main.cpp -s NO_EXIT_RUNTIME=1 -s -s EXPORTED_FUNCTIONS="_PrintToBrowser","_main","_help" -sEXPORTED_RUNTIME_METHODS=ccall -s  -DEMSCRIPTENBUILD
#INVOKE_RUN=0
