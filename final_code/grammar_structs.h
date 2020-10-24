/* Header guard */
#ifndef GRAMMAR_STRUCT_H
#define GRAMMAR_STRUCT_H
/***************/
#include <stdio.h>
#include <string.h>
typedef enum { false, true } bool;

typedef enum { // list all the non terminals or terminals
    arithmeticexpr,
    assign_stmt,
    assign_stmts,
    boolexpr,
    decl_jagged,
    decl_non_jagged,
    decl_stmt,
    decl_stmts,
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
    list_of_identifiers,
    logfactor,
    logterm,
    main_program,
    primitive_type,
    range_list,
    rect_array,
    stmts,
    term,
    value_list,
    var,
    var_lhs,
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
    PROGRAM,
    R1,
    REAL,
    RPAREN,
    SEMICOLON,
    SIZE,
    SQBC,
    SQBO,
    UNKNOWN,
    VALUES,
    VARIABLES,
} BaseSymbol;

typedef struct symbol { // symbol with info if it is terminal or not
    bool is_terminal;
    BaseSymbol s;
} Symbol;

Symbol toSymbol(char *enustr);
char *toStringSymbol(Symbol symb);
void printSymbol(Symbol symb);

#endif
