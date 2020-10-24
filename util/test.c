#include "./output_file_structs.h"

int main(){
    Symbol sym = toSymbol("fact");
    printSymbol(sym);
    sym = toSymbol("{");
    printSymbol(sym);
    sym = toSymbol("}");
    printSymbol(sym);
    sym = toSymbol("size");
    printSymbol(sym);
    sym = toSymbol("values");
    printSymbol(sym);
    sym = toSymbol("(");
    printSymbol(sym);
    sym = toSymbol("main_program");
    printSymbol(sym);
    sym = toSymbol("program");
    printSymbol(sym);
}
