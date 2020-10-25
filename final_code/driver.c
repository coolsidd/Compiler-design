#include <stdlib.h>
#include "grammar.h"
#include "tokenizer_structs.h"
#include "parse_tree.h"
#include "traverse_parse.c"

int main(int argc, char** argv){
    Grammar* g = (Grammar*)malloc(sizeof(Grammar));
    g->num_rules = 0;
    g->start_symb = toSymbol("main_program");
    g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule));
    readGrammar("./grammar/machine_grammar.txt", g);
    printGrammar(g);
    TokenStream *s = newTokenStream();
    tokenizeSourceCode(argv[1], s);
    /* for(Token *temp = s->head; temp; temp=temp->next){ */
    /*      printSymbol(temp->lexeme); */
    /* } */
    Parse_tree_node * p;
    p = createParseTree(s,g);
    traverseParseTree(p, 0);
    return 0;
}

/* int main() { */
/*     Grammar* g = (Grammar*)malloc(sizeof(Grammar)); */
/*     g->num_rules = 0; */
/*     g->start_symb = toSymbol("program"); */
/*     g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule)); */
/*     readGrammar("grammar/machine_grammar.txt", g); */
/*     //printGrammar(g); */

/*     TokenStream *s = newTokenStream(); */
/*     tokenizeSourceCode("sample_code_2.txt", s); */
/*     //for(Token *temp = s->head; temp; temp=temp->next) { */
/*     //    printSymbol(temp->lexeme); */
/*     //} */

/*     Parse_tree_node * p; */
/*     p = createParseTree(s,g); */
/* } */
