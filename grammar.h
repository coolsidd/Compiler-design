/* Header guard */
#ifndef GRAMMAR_H
#define GRAMMAR_H
/***************/

typedef enum {false, true} bool;

typedef enum{ // list all the non terminals or terminals
    arithmeticexpr,
    array_type,
    assignment_stmt,
    boolexpr,
    code_stmt,
    declaration_stmt,
    declaration_type,
    expr,
    fact,
    id_list,
    index_list,
    j2list,
    j3list,
    jagged2init,
    jagged2list,
    jagged3init,
    jagged3list,
    jagged_array,
    jagged_list,
    list_of_identifiers,
    logfactor,
    logterm,
    main_program,
    primitive_type,
    program,
    range_list,
    rect_array,
    term,
    value_list,
    var,
    AND,
    ARRAY,
    BOOLEAN,
    COLON,
    CONST,
    CURLYCLOSE,
    CURLYOPEN,
    DECLARE,
    DIV,
    ELIPSIS,
    EQUALS,
    FALSE,
    ID,
    INTEGER,
    JAGGED,
    LIST,
    LPAREN,
    MINUS,
    MULT,
    OF,
    OR,
    PLUS,
    R1,
    REAL,
    RPAREN,
    SEMICOLON,
    SIZE,
    SQBC,
    SQBO,
    TRUE,
    VALUES,
    VARIABLES,
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
    Symbol lhs;
    RuleNode *rhs; // linked list of rules
} Rule;

typedef struct grammar { // Final data structure for
    int num_rules;
    Symbol start_symb;
    Rule* rules; // array of size max_rules consisting of a linked list of rules
} Grammar;

#endif
