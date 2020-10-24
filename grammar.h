/* Header guard */
#ifndef GRAMMAR_H
#define GRAMMAR_H
/***************/

#include "./util/output_file_structs.h"

//typedef struct symbol Symbol;

typedef struct rule_node { // node for linkedlist of symbols (for LHS of rule list)
    Symbol s;
    struct rule_node *next;
} RuleNode;

typedef struct rule { // LHS -> linked list of symbols (RHS)
    Symbol lhs;
    RuleNode *rhs; // linked list of rules
} Rule;

typedef struct grammar { // Final data structure for
    int num_rules;
    Symbol start_symb;
    Rule* rules; // array of size max_rules consisting of a linked list of rules
} Grammar;

#endif
