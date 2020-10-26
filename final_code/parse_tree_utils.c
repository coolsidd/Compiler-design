//#include "traverse_parse.h"
#include "parse_tree.h"
#include "grammar_structs.h"

void printLine(char* symb, bool t, char* typ, char* name, int line, int depth) {
    if (t) {
        printf("|%20s|%20s|%20s|%20s|%5d|%5d|\n", symb, "terminal", typ, name, line, depth);
    } else {
        printf("|%20s|%20s|%20s|%20s|%5d|%5d|\n", symb, "non-terminal", typ, name, line, depth);
    }
}

void printParseTree(Parse_tree_node *p, int d) {
    if (d == 0)
        printf("|%20s|%20s|%20s|%20s|%5s|%5s|\n",
        "Symbol", "term / non-term", "Type", "Name", "num", "Depth");

    printLine(  p->tok->token_name,
                p->tok->lexeme.is_terminal,
                "***",
                toStringSymbol(p->tok->lexeme),
                p->tok->line_no, d);
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
