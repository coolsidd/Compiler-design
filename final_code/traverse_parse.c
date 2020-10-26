//#include "traverse_parse.h"
#include "parse_tree.h"

void traverseParseTree(Parse_tree_node *p, int height) {
    printf("%d. At node %s\n", height, toStringSymbol(p->tok->lexeme));
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
