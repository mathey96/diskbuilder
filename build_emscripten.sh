emcc main.cpp -o index.html -s NO_EXIT_RUNTIME=1 -s -s EXPORTED_FUNCTIONS="_PrintToBrowser","_main","_help","_PrintToJson" -sEXPORTED_RUNTIME_METHODS=ccall -s  -DEMSCRIPTENBUILD
#INVOKE_RUN=0
