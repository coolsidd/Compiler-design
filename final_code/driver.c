#include <stdlib.h>
#include "grammar.h"
#include "tokenizer_structs.h"
#include "grammar_structs.h"

int main() {
    Grammar* g = (Grammar*)malloc(sizeof(Grammar));
    g->num_rules = 0;
    g->start_symb = toSymbol("program");
    g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule));
    readGrammar("grammar/machine_grammar.txt", g);
    printGrammar(g);

    TokenStream *s = newTokenStream();
    tokenizeSourceCode("sample_code_1.txt", s);
    for(Token *temp = s->head; temp; temp=temp->next) {
        printSymbol(temp->lexeme);
    }
}
