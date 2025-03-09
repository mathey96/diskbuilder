emcc main.cpp -o index.js -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="_PrintToBrowser","_help","_PrintToJson" -sEXPORTED_RUNTIME_METHODS=ccall -s  -DEMSCRIPTENBUILD
#INVOKE_RUN=0
