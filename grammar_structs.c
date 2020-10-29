#include "grammar_structs.h"
#include <stdio.h>
#include <string.h>

Symbol toSymbol(char *enustr) {
    Symbol ans;
    ans.is_terminal = false;
    ans.s = UNKNOWN;
    if (strcmp(enustr, "&&&") == 0) {
        ans.is_terminal = true;
        ans.s = AND;
        return ans;
    }

    if (strcmp(enustr, "array") == 0) {
        ans.is_terminal = true;
        ans.s = ARRAY;
        return ans;
    }

    if (strcmp(enustr, "boolean") == 0) {
        ans.is_terminal = true;
        ans.s = BOOLEAN;
        return ans;
    }

    if (strcmp(enustr, ":") == 0) {
        ans.is_terminal = true;
        ans.s = COLON;
        return ans;
    }

    if (strcmp(enustr, "CONST") == 0) {
        ans.is_terminal = true;
        ans.s = CONST;
        return ans;
    }

    if (strcmp(enustr, "}") == 0) {
        ans.is_terminal = true;
        ans.s = CURLYCLOSE;
        return ans;
    }

    if (strcmp(enustr, "{") == 0) {
        ans.is_terminal = true;
        ans.s = CURLYOPEN;
        return ans;
    }

    if (strcmp(enustr, "declare") == 0) {
        ans.is_terminal = true;
        ans.s = DECLARE;
        return ans;
    }

    if (strcmp(enustr, "/") == 0) {
        ans.is_terminal = true;
        ans.s = DIV;
        return ans;
    }

    if (strcmp(enustr, "..") == 0) {
        ans.is_terminal = true;
        ans.s = ELIPSIS;
        return ans;
    }

    if (strcmp(enustr, "=") == 0) {
        ans.is_terminal = true;
        ans.s = EQUALS;
        return ans;
    }

    if (strcmp(enustr, "ID") == 0) {
        ans.is_terminal = true;
        ans.s = ID;
        return ans;
    }

    if (strcmp(enustr, "integer") == 0) {
        ans.is_terminal = true;
        ans.s = INTEGER;
        return ans;
    }

    if (strcmp(enustr, "jagged") == 0) {
        ans.is_terminal = true;
        ans.s = JAGGED;
        return ans;
    }

    if (strcmp(enustr, "list") == 0) {
        ans.is_terminal = true;
        ans.s = LIST;
        return ans;
    }

    if (strcmp(enustr, "(") == 0) {
        ans.is_terminal = true;
        ans.s = LPAREN;
        return ans;
    }

    if (strcmp(enustr, "-") == 0) {
        ans.is_terminal = true;
        ans.s = MINUS;
        return ans;
    }

    if (strcmp(enustr, "*") == 0) {
        ans.is_terminal = true;
        ans.s = MULT;
        return ans;
    }

    if (strcmp(enustr, "of") == 0) {
        ans.is_terminal = true;
        ans.s = OF;
        return ans;
    }

    if (strcmp(enustr, "|||") == 0) {
        ans.is_terminal = true;
        ans.s = OR;
        return ans;
    }

    if (strcmp(enustr, "+") == 0) {
        ans.is_terminal = true;
        ans.s = PLUS;
        return ans;
    }

    if (strcmp(enustr, "program") == 0) {
        ans.is_terminal = true;
        ans.s = PROGRAM;
        return ans;
    }

    if (strcmp(enustr, "R1") == 0) {
        ans.is_terminal = true;
        ans.s = R1;
        return ans;
    }

    if (strcmp(enustr, "real") == 0) {
        ans.is_terminal = true;
        ans.s = REAL;
        return ans;
    }

    if (strcmp(enustr, ")") == 0) {
        ans.is_terminal = true;
        ans.s = RPAREN;
        return ans;
    }

    if (strcmp(enustr, ";") == 0) {
        ans.is_terminal = true;
        ans.s = SEMICOLON;
        return ans;
    }

    if (strcmp(enustr, "size") == 0) {
        ans.is_terminal = true;
        ans.s = SIZE;
        return ans;
    }

    if (strcmp(enustr, "]") == 0) {
        ans.is_terminal = true;
        ans.s = SQBC;
        return ans;
    }

    if (strcmp(enustr, "[") == 0) {
        ans.is_terminal = true;
        ans.s = SQBO;
        return ans;
    }

    if (strcmp(enustr, "UNKNOWN") == 0) {
        ans.is_terminal = true;
        ans.s = UNKNOWN;
        return ans;
    }

    if (strcmp(enustr, "values") == 0) {
        ans.is_terminal = true;
        ans.s = VALUES;
        return ans;
    }

    if (strcmp(enustr, "variables") == 0) {
        ans.is_terminal = true;
        ans.s = VARIABLES;
        return ans;
    }

    if (strcmp(enustr, "arithmeticexpr") == 0) {
        ans.is_terminal = false;
        ans.s = arithmeticexpr;
        return ans;
    }

    if (strcmp(enustr, "assign_stmt") == 0) {
        ans.is_terminal = false;
        ans.s = assign_stmt;
        return ans;
    }

    if (strcmp(enustr, "assign_stmts") == 0) {
        ans.is_terminal = false;
        ans.s = assign_stmts;
        return ans;
    }

    if (strcmp(enustr, "decl_jagged") == 0) {
        ans.is_terminal = false;
        ans.s = decl_jagged;
        return ans;
    }

    if (strcmp(enustr, "decl_non_jagged") == 0) {
        ans.is_terminal = false;
        ans.s = decl_non_jagged;
        return ans;
    }

    if (strcmp(enustr, "decl_stmt") == 0) {
        ans.is_terminal = false;
        ans.s = decl_stmt;
        return ans;
    }

    if (strcmp(enustr, "decl_stmts") == 0) {
        ans.is_terminal = false;
        ans.s = decl_stmts;
        return ans;
    }

    if (strcmp(enustr, "declaration_type") == 0) {
        ans.is_terminal = false;
        ans.s = declaration_type;
        return ans;
    }

    if (strcmp(enustr, "expr") == 0) {
        ans.is_terminal = false;
        ans.s = expr;
        return ans;
    }

    if (strcmp(enustr, "fact") == 0) {
        ans.is_terminal = false;
        ans.s = fact;
        return ans;
    }

    if (strcmp(enustr, "id_list") == 0) {
        ans.is_terminal = false;
        ans.s = id_list;
        return ans;
    }

    if (strcmp(enustr, "index_list") == 0) {
        ans.is_terminal = false;
        ans.s = index_list;
        return ans;
    }

    if (strcmp(enustr, "j2list") == 0) {
        ans.is_terminal = false;
        ans.s = j2list;
        return ans;
    }

    if (strcmp(enustr, "j3list") == 0) {
        ans.is_terminal = false;
        ans.s = j3list;
        return ans;
    }

    if (strcmp(enustr, "jagged2init") == 0) {
        ans.is_terminal = false;
        ans.s = jagged2init;
        return ans;
    }

    if (strcmp(enustr, "jagged2list") == 0) {
        ans.is_terminal = false;
        ans.s = jagged2list;
        return ans;
    }

    if (strcmp(enustr, "jagged3init") == 0) {
        ans.is_terminal = false;
        ans.s = jagged3init;
        return ans;
    }

    if (strcmp(enustr, "jagged3list") == 0) {
        ans.is_terminal = false;
        ans.s = jagged3list;
        return ans;
    }

    if (strcmp(enustr, "jagged_array") == 0) {
        ans.is_terminal = false;
        ans.s = jagged_array;
        return ans;
    }

    if (strcmp(enustr, "list_of_identifiers") == 0) {
        ans.is_terminal = false;
        ans.s = list_of_identifiers;
        return ans;
    }

    if (strcmp(enustr, "main_program") == 0) {
        ans.is_terminal = false;
        ans.s = main_program;
        return ans;
    }

    if (strcmp(enustr, "primitive_type") == 0) {
        ans.is_terminal = false;
        ans.s = primitive_type;
        return ans;
    }

    if (strcmp(enustr, "range_list") == 0) {
        ans.is_terminal = false;
        ans.s = range_list;
        return ans;
    }

    if (strcmp(enustr, "rect_array") == 0) {
        ans.is_terminal = false;
        ans.s = rect_array;
        return ans;
    }

    if (strcmp(enustr, "stmts") == 0) {
        ans.is_terminal = false;
        ans.s = stmts;
        return ans;
    }

    if (strcmp(enustr, "term") == 0) {
        ans.is_terminal = false;
        ans.s = term;
        return ans;
    }

    if (strcmp(enustr, "value_list") == 0) {
        ans.is_terminal = false;
        ans.s = value_list;
        return ans;
    }

    if (strcmp(enustr, "var") == 0) {
        ans.is_terminal = false;
        ans.s = var;
        return ans;
    }

    if (strcmp(enustr, "var_lhs") == 0) {
        ans.is_terminal = false;
        ans.s = var_lhs;
        return ans;
    }

    return ans;
}

char *toStringSymbol(Symbol symb) {
    switch (symb.s) {
    case (AND):
        return "AND";
        break;
    case (ARRAY):
        return "ARRAY";
        break;
    case (BOOLEAN):
        return "BOOLEAN";
        break;
    case (COLON):
        return "COLON";
        break;
    case (CONST):
        return "CONST";
        break;
    case (CURLYCLOSE):
        return "CURLYCLOSE";
        break;
    case (CURLYOPEN):
        return "CURLYOPEN";
        break;
    case (DECLARE):
        return "DECLARE";
        break;
    case (DIV):
        return "DIV";
        break;
    case (ELIPSIS):
        return "ELIPSIS";
        break;
    case (EQUALS):
        return "EQUALS";
        break;
    case (ID):
        return "ID";
        break;
    case (INTEGER):
        return "INTEGER";
        break;
    case (JAGGED):
        return "JAGGED";
        break;
    case (LIST):
        return "LIST";
        break;
    case (LPAREN):
        return "LPAREN";
        break;
    case (MINUS):
        return "MINUS";
        break;
    case (MULT):
        return "MULT";
        break;
    case (OF):
        return "OF";
        break;
    case (OR):
        return "OR";
        break;
    case (PLUS):
        return "PLUS";
        break;
    case (PROGRAM):
        return "PROGRAM";
        break;
    case (R1):
        return "R1";
        break;
    case (REAL):
        return "REAL";
        break;
    case (RPAREN):
        return "RPAREN";
        break;
    case (SEMICOLON):
        return "SEMICOLON";
        break;
    case (SIZE):
        return "SIZE";
        break;
    case (SQBC):
        return "SQBC";
        break;
    case (SQBO):
        return "SQBO";
        break;
    case (UNKNOWN):
        return "UNKNOWN";
        break;
    case (VALUES):
        return "VALUES";
        break;
    case (VARIABLES):
        return "VARIABLES";
        break;
    case (arithmeticexpr):
        return "arithmeticexpr";
        break;
    case (assign_stmt):
        return "assign_stmt";
        break;
    case (assign_stmts):
        return "assign_stmts";
        break;
    case (decl_jagged):
        return "decl_jagged";
        break;
    case (decl_non_jagged):
        return "decl_non_jagged";
        break;
    case (decl_stmt):
        return "decl_stmt";
        break;
    case (decl_stmts):
        return "decl_stmts";
        break;
    case (declaration_type):
        return "declaration_type";
        break;
    case (expr):
        return "expr";
        break;
    case (fact):
        return "fact";
        break;
    case (id_list):
        return "id_list";
        break;
    case (index_list):
        return "index_list";
        break;
    case (j2list):
        return "j2list";
        break;
    case (j3list):
        return "j3list";
        break;
    case (jagged2init):
        return "jagged2init";
        break;
    case (jagged2list):
        return "jagged2list";
        break;
    case (jagged3init):
        return "jagged3init";
        break;
    case (jagged3list):
        return "jagged3list";
        break;
    case (jagged_array):
        return "jagged_array";
        break;
    case (list_of_identifiers):
        return "list_of_identifiers";
        break;
    case (main_program):
        return "main_program";
        break;
    case (primitive_type):
        return "primitive_type";
        break;
    case (range_list):
        return "range_list";
        break;
    case (rect_array):
        return "rect_array";
        break;
    case (stmts):
        return "stmts";
        break;
    case (term):
        return "term";
        break;
    case (value_list):
        return "value_list";
        break;
    case (var):
        return "var";
        break;
    case (var_lhs):
        return "var_lhs";
        break;
    }
}
void printSymbol(Symbol symb) {
    printf("Symbol variable : ");
    printf("%s", toStringSymbol(symb));
    printf("    is_terminal : %s\n", symb.is_terminal ? "true" : "false");
}
