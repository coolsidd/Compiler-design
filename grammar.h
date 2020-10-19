/* Header guard */
#ifndef GRAMMAR_H
#define GRAMMAR_H
/***************/

typedef enum {false, true} bool;

typedef enum { // list all the non terminals
    program,
    statements,
    statement
} NonTerminal;

typedef enum { // list all the terminals
    DECLARE,
    ID,
    SEMICOLON,
    AND,
    OR,
    NUM
} Terminal;

typedef union base_symb { // symbol can either be a terminal or a non-terminal
	Terminal t;
	NonTerminal nt;
} BaseSymbol;

typedef struct symb { // symbol with info if it is terminal or not
	bool is_terminal;
	BaseSymbol s;
} Symbol;

typedef struct rule_node { // node for linkedlist of symbols (for LHS of rule list)
    Symbol s;
    struct rule_node *next;
} RuleNode;

typedef struct rule { // LHS -> linked list of symbols (RHS)
    NonTerminal lhs;
    int rhs_len;
    RuleNode *rhs; // linked list of rules
} Rule;

typedef struct grammar { // Final data structure for
    int num_rules;
    NonTerminal start_symb;
    Rule* rules; // array of size max_rules consisting of a linked list of rules
} Grammar;

#endif
