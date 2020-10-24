#ifndef __PARSE_TREE_H_
#define __PARSE_TREE_H_

#include <stdlib.h>
#include "./grammar.h"
#include "./tokenizer_structs.h"
#include "./util/output_file_structs.h"

typedef struct parse_tree_node {
    int num_children;
    struct parse_tree_node *child;
    struct parse_tree_node *last_child;
    struct parse_tree_node *next;
    Token *tok;
} Parse_tree_node;

void createParseTree(Parse_tree_node* t, TokenStream *s, Grammar *g);
Parse_tree_node *recursiveParseNonterminal(Symbol symb, Token ** tstr, Grammar *g);
Parse_tree_node* new_parse_tree();
void free_parse_tree(Parse_tree_node *root);
void add_parsed_child(Parse_tree_node *root, Parse_tree_node *node);

#endif // __PARSE_TREE_STRUCTS_H_