#include <stdlib.h>
#include "grammar.h"
#include "tokenizer_structs.h"
#include "parse_tree.h"
#include "../data_structures/TypeExpressionDS/print.h"
#include "../data_structures/TypeExpressionDS/type_exp_table.h"

#define MAXLINELEN 2048
#define MAXRULES 100
//#define DEBUG /* for debug mode */

int main(int argc, char** argv){

    if (argc < 2) {
        printf("Usage: ./driver.exe <filename>\n");
        exit(1);
    }

    printf("Reading grammar from grammar/machine_grammar.txt ...\n");
    Grammar* g = (Grammar*)malloc(sizeof(Grammar));
    g->num_rules = 0;
    g->start_symb = toSymbol("main_program");
    g->rules = (Rule*)malloc(MAXRULES*sizeof(Rule));
    int gflag = readGrammar("grammar/machine_grammar.txt", g);
    #ifdef DEBUG
        printGrammar(g);
    #endif
    if (!gflag) exit(1);
    else printf("parsed grammar successfully\n\n");

    printf("Tokenizing %s ...\n", argv[1]);
    TokenStream *s = newTokenStream();
    int  tflag = tokenizeSourceCode(argv[1], s);
    #ifdef DEBUG
        for(Token *temp = s->head; temp; temp=temp->next) {
            printSymbol(temp->lexeme);
        }
    #endif
    if (!tflag) exit(1);
    else printf("tokenized successfully\n\n");

    int option, line=0;
    Parse_tree_node * p;

    do {

        printf("\n\nMenu: \n");
        printf("--------------------------------------------------------\n");
        printf("0 - Exit\n");
        printf("1 - Create parse tree\n");
        printf("2 - Traverse parse tree, create Type expression table, display type errors\n");
        printf("3 - print parse tree\n");
        printf("4 - print type expression table\n");
        printf("--------------------------------------------------------\n");

        printf("> ");
        scanf("%d",&option);

        switch(option){
            case 0:
                break;
            case 1:
            {
                printf("Creating parse tree ...\n");
                line = 0;
                p = createParseTree(s,g,&line);
                if (!p) {
                    printf("Syntax error while reading %s\nSuccessfully read till line: %d\n", argv[1], line);
                    exit(1);
                }
                else printf("parse tree created successfully\n\n");

                break;
            }
            case 2:
            {
                type_exp_table *t = create_type_expression_table();
                printf("Creating parse tree ...\n");
                line = 0;
                p = createParseTree(s,g,&line);
                if (!p) {
                    printf("Syntax error while reading %s\nSuccessfully read till line: %d\n", argv[1], line);
                    exit(1);
                }
                else printf("parse tree created successfully\n\n");
                traverse_and_populate(t, p);
                break;
            }
            case 3:
            {
                printf("Creating parse tree ...\n");
                line = 0;
                p = createParseTree(s,g,&line);
                if (!p) {
                    printf("Syntax error while reading %s\nSuccessfully read till line: %d\n", argv[1], line);
                    exit(1);
                }
                else printf("parse tree created successfully\n\n");
                printParseTree(p,0);
                printf("\n");
                break;
            }
            case 4:
            {
                type_exp_table *t = create_type_expression_table();
                printf("Creating parse tree ...\n");
                line = 0;
                p = createParseTree(s, g, &line);
                if (!p)
                {
                    printf("Syntax error while reading %s\nSuccessfully read till line: %d\n", argv[1], line);
                    exit(1);
                }
                else
                    printf("parse tree created successfully\n\n");
                traverse_and_populate(t, p);
                printf("Populated Type expression table successfully\n");
                print_type_exp_table(t);
                printParseTree(p, 0);
                break;
            }
            default:
                printf("invalid input\n");
                break;
        }

    } while(option != 0);
}
