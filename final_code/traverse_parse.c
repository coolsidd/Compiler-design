//#include "traverse_parse.h"
#include "parse_tree.h"

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
