/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#include "parse_tree.h"

void printLine(char* symb, bool t, char* typ, char* name, int line, int depth) {
    if (t) {
        printf("|%20s|%20s|%20s|%20s|%5d|%5d|\n", symb, "terminal", typ, name, line, depth);
    } else {
        printf("|%20s|%20s|%20s|%20s|%5d|%5d|\n", symb, "non-terminal", typ, name, line, depth);
    }
}

void printParseTree(Parse_tree_node *p, int d) {
    if (d == 0) {
        printf("\n%45s","|Parse tree|\n\n");
        printf("|%20s|%20s|%20s|%20s|%5s|%5s|\n",
        "Symbol", "term / non-term", "Type", "Name", "num", "Depth");
    }
    type_expression* txp = NULL;
    Parse_tree_node *tempP = p;
    while(tempP->parent){
        switch(tempP->tok->lexeme.s){
            case main_program:{
                break;
            }
            case decl_stmt:{
                txp = tempP->txp;
                break;
            }
            case assign_stmt:{
                txp = tempP->txp;
                break;
            }
        }
        tempP = tempP->parent;
    }

    printLine(  p->tok->token_name,
                p->tok->lexeme.is_terminal,
                txp?get_string_representation(txp):"***",
                toStringSymbol(p->tok->lexeme),
                p->tok->line_no, p->depth);
    if(d!=p->depth){
        printf("ERROR depth mismatch\n");
        printf("%d vs %d\n", d, p->depth);
    }
    for (Parse_tree_node *temp_child = p->child; temp_child;
         temp_child = temp_child->next) {
        printParseTree(temp_child, d + 1);
    }
}


void traverseParseTree(Parse_tree_node *p, int height) {
    if(!p->tok->lexeme.is_terminal)
        printf("%d. At node %s\n", height, toStringSymbol(p->tok->lexeme));
    else
        printf("%d. At node %s\n", height, p->tok->token_name);
    switch (p->tok->lexeme.s) {
    case ID: // call your functions here
        break;
    case rect_array:
        // call your functions
        break;
    case j2list:
        break;
    }
    for (Parse_tree_node *temp_child = p->child; temp_child;
         temp_child = temp_child->next) {
        traverseParseTree(temp_child, height + 1);
    }
}
