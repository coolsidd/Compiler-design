#include "./output_file_structs.h"
#include "./output_file_structs.c"
#include "./other_structs.h"

int main(){
    Symbol sym = toSymbol("fact");
    printSymbol(sym);
    sym = toSymbol("{");
    printSymbol(sym);
    sym = toSymbol("}");
    printSymbol(sym);
}
