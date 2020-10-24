#include <stdlib.h>
#include "grammar.h"
#include "tokenizer_structs.h"
#include "parse_tree.h"

int main() {
    Grammar* g = (Grammar*)malloc(sizeof(Grammar));
    g->num_rules = 0;
    g->start_symb = toSymbol("program");
    g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule));
    readGrammar("grammar/machine_grammar.txt", g);
    //printGrammar(g);

    TokenStream *s = newTokenStream();
    tokenizeSourceCode("sample_code_2.txt", s);
    //for(Token *temp = s->head; temp; temp=temp->next) {
    //    printSymbol(temp->lexeme);
    //}

    Parse_tree_node * p;
    p = createParseTree(s,g);
}
