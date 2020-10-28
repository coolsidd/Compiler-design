/*
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70636P Aditya Tulsyan
*/

#ifndef __PARSE_TREE_H_
#define __PARSE_TREE_H_

#include <stdlib.h>
#include "grammar.h"
#include "tokenizer_structs.h"

typedef struct ____TYPE_EXPRESSION____ type_expression;
char * get_string_representation(type_expression * txp);

typedef struct parse_tree_node {
    int num_children;
    struct parse_tree_node *child;
    struct parse_tree_node *last_child;
    struct parse_tree_node *next;
    struct parse_tree_node *parent;
    type_expression* txp;
    Token *tok;
    int depth;
} Parse_tree_node;

Parse_tree_node *getNodeFromIndex(Parse_tree_node *p, int index);
Parse_tree_node *createParseTree(TokenStream *s, Grammar *g, int *maxline);
Parse_tree_node *recursiveParseNonterminal(Symbol symb, Token ** tstr, Grammar *g, int *maxline, int depth);
Parse_tree_node *new_parse_tree();
void free_parse_tree(Parse_tree_node *root);
void add_parsed_child(Parse_tree_node *root, Parse_tree_node *node);
void printLine(char* symb, bool t, char* typ, char* name, int line, int depth);
void printParseTree(Parse_tree_node *p, int d);
void traverseParseTree(Parse_tree_node *p, int height);

#endif
