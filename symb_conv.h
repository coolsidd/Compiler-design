#include <stdio.h>
#include <string.h>

Symbol toSymbol(char *enustr) {
    Symbol* ans = (Symbol*)malloc(sizeof(Symbol));
    if (strcmp(enustr, "COLON") == 0) {
        ans->is_terminal = true;
        ans->s = COLON;
        return *ans;
    }

    if (strcmp(enustr, "PLUS") == 0) {
        ans->is_terminal = true;
        ans->s = PLUS;
        return *ans;
    }

    if (strcmp(enustr, "MULT") == 0) {
        ans->is_terminal = true;
        ans->s = MULT;
        return *ans;
    }

    if (strcmp(enustr, "DIV") == 0) {
        ans->is_terminal = true;
        ans->s = DIV;
        return *ans;
    }

    if (strcmp(enustr, "FALSE") == 0) {
        ans->is_terminal = true;
        ans->s = FALSE;
        return *ans;
    }

    if (strcmp(enustr, "OF") == 0) {
        ans->is_terminal = true;
        ans->s = OF;
        return *ans;
    }

    if (strcmp(enustr, "CONST") == 0) {
        ans->is_terminal = true;
        ans->s = CONST;
        return *ans;
    }

    if (strcmp(enustr, "JAGGED") == 0) {
        ans->is_terminal = true;
        ans->s = JAGGED;
        return *ans;
    }

    if (strcmp(enustr, "INTEGER") == 0) {
        ans->is_terminal = true;
        ans->s = INTEGER;
        return *ans;
    }

    if (strcmp(enustr, "LIST") == 0) {
        ans->is_terminal = true;
        ans->s = LIST;
        return *ans;
    }

    if (strcmp(enustr, "REAL") == 0) {
        ans->is_terminal = true;
        ans->s = REAL;
        return *ans;
    }

    if (strcmp(enustr, "ARRAY") == 0) {
        ans->is_terminal = true;
        ans->s = ARRAY;
        return *ans;
    }

    if (strcmp(enustr, "SQBC") == 0) {
        ans->is_terminal = true;
        ans->s = SQBC;
        return *ans;
    }

    if (strcmp(enustr, "OR") == 0) {
        ans->is_terminal = true;
        ans->s = OR;
        return *ans;
    }

    if (strcmp(enustr, "LPAREN") == 0) {
        ans->is_terminal = true;
        ans->s = LPAREN;
        return *ans;
    }

    if (strcmp(enustr, "CURLYOPEN") == 0) {
        ans->is_terminal = true;
        ans->s = CURLYOPEN;
        return *ans;
    }

    if (strcmp(enustr, "VALUES") == 0) {
        ans->is_terminal = true;
        ans->s = VALUES;
        return *ans;
    }

    if (strcmp(enustr, "BOOLEAN") == 0) {
        ans->is_terminal = true;
        ans->s = BOOLEAN;
        return *ans;
    }

    if (strcmp(enustr, "DECLARE") == 0) {
        ans->is_terminal = true;
        ans->s = DECLARE;
        return *ans;
    }

    if (strcmp(enustr, "SEMICOLON") == 0) {
        ans->is_terminal = true;
        ans->s = SEMICOLON;
        return *ans;
    }

    if (strcmp(enustr, "CURLYCLOSE") == 0) {
        ans->is_terminal = true;
        ans->s = CURLYCLOSE;
        return *ans;
    }

    if (strcmp(enustr, "R1") == 0) {
        ans->is_terminal = true;
        ans->s = R1;
        return *ans;
    }

    if (strcmp(enustr, "EQUALS") == 0) {
        ans->is_terminal = true;
        ans->s = EQUALS;
        return *ans;
    }

    if (strcmp(enustr, "MINUS") == 0) {
        ans->is_terminal = true;
        ans->s = MINUS;
        return *ans;
    }

    if (strcmp(enustr, "ID") == 0) {
        ans->is_terminal = true;
        ans->s = ID;
        return *ans;
    }

    if (strcmp(enustr, "AND") == 0) {
        ans->is_terminal = true;
        ans->s = AND;
        return *ans;
    }

    if (strcmp(enustr, "TRUE") == 0) {
        ans->is_terminal = true;
        ans->s = TRUE;
        return *ans;
    }

    if (strcmp(enustr, "SIZE") == 0) {
        ans->is_terminal = true;
        ans->s = SIZE;
        return *ans;
    }

    if (strcmp(enustr, "SQBO") == 0) {
        ans->is_terminal = true;
        ans->s = SQBO;
        return *ans;
    }

    if (strcmp(enustr, "RPAREN") == 0) {
        ans->is_terminal = true;
        ans->s = RPAREN;
        return *ans;
    }

    if (strcmp(enustr, "VARIABLES") == 0) {
        ans->is_terminal = true;
        ans->s = VARIABLES;
        return *ans;
    }

    if (strcmp(enustr, "ELIPSIS") == 0) {
        ans->is_terminal = true;
        ans->s = ELIPSIS;
        return *ans;
    }

    if (strcmp(enustr, "index_list") == 0) {
        ans->is_terminal = false;
        ans->s = index_list;
        return *ans;
    }

    if (strcmp(enustr, "fact") == 0) {
        ans->is_terminal = false;
        ans->s = fact;
        return *ans;
    }

    if (strcmp(enustr, "boolexpr") == 0) {
        ans->is_terminal = false;
        ans->s = boolexpr;
        return *ans;
    }

    if (strcmp(enustr, "declaration_stmt") == 0) {
        ans->is_terminal = false;
        ans->s = declaration_stmt;
        return *ans;
    }

    if (strcmp(enustr, "primitive_type") == 0) {
        ans->is_terminal = false;
        ans->s = primitive_type;
        return *ans;
    }

    if (strcmp(enustr, "program") == 0) {
        ans->is_terminal = false;
        ans->s = program;
        return *ans;
    }

    if (strcmp(enustr, "expr") == 0) {
        ans->is_terminal = false;
        ans->s = expr;
        return *ans;
    }

    if (strcmp(enustr, "arithmeticexpr") == 0) {
        ans->is_terminal = false;
        ans->s = arithmeticexpr;
        return *ans;
    }

    if (strcmp(enustr, "main_program") == 0) {
        ans->is_terminal = false;
        ans->s = main_program;
        return *ans;
    }

    if (strcmp(enustr, "range_list") == 0) {
        ans->is_terminal = false;
        ans->s = range_list;
        return *ans;
    }

    if (strcmp(enustr, "jagged3list") == 0) {
        ans->is_terminal = false;
        ans->s = jagged3list;
        return *ans;
    }

    if (strcmp(enustr, "code_stmt") == 0) {
        ans->is_terminal = false;
        ans->s = code_stmt;
        return *ans;
    }

    if (strcmp(enustr, "jagged2list") == 0) {
        ans->is_terminal = false;
        ans->s = jagged2list;
        return *ans;
    }

    if (strcmp(enustr, "j2list") == 0) {
        ans->is_terminal = false;
        ans->s = j2list;
        return *ans;
    }

    if (strcmp(enustr, "term") == 0) {
        ans->is_terminal = false;
        ans->s = term;
        return *ans;
    }

    if (strcmp(enustr, "list_of_identifiers") == 0) {
        ans->is_terminal = false;
        ans->s = list_of_identifiers;
        return *ans;
    }

    if (strcmp(enustr, "jagged3init") == 0) {
        ans->is_terminal = false;
        ans->s = jagged3init;
        return *ans;
    }

    if (strcmp(enustr, "var") == 0) {
        ans->is_terminal = false;
        ans->s = var;
        return *ans;
    }

    if (strcmp(enustr, "jagged2init") == 0) {
        ans->is_terminal = false;
        ans->s = jagged2init;
        return *ans;
    }

    if (strcmp(enustr, "assignment_stmt") == 0) {
        ans->is_terminal = false;
        ans->s = assignment_stmt;
        return *ans;
    }

    if (strcmp(enustr, "declaration_type") == 0) {
        ans->is_terminal = false;
        ans->s = declaration_type;
        return *ans;
    }

    if (strcmp(enustr, "rect_array") == 0) {
        ans->is_terminal = false;
        ans->s = rect_array;
        return *ans;
    }

    if (strcmp(enustr, "value_list") == 0) {
        ans->is_terminal = false;
        ans->s = value_list;
        return *ans;
    }

    if (strcmp(enustr, "array_type") == 0) {
        ans->is_terminal = false;
        ans->s = array_type;
        return *ans;
    }

    if (strcmp(enustr, "id_list") == 0) {
        ans->is_terminal = false;
        ans->s = id_list;
        return *ans;
    }

    if (strcmp(enustr, "logterm") == 0) {
        ans->is_terminal = false;
        ans->s = logterm;
        return *ans;
    }

    if (strcmp(enustr, "logfactor") == 0) {
        ans->is_terminal = false;
        ans->s = logfactor;
        return *ans;
    }

    if (strcmp(enustr, "jagged_array") == 0) {
        ans->is_terminal = false;
        ans->s = jagged_array;
        return *ans;
    }

    if (strcmp(enustr, "jagged_list") == 0) {
        ans->is_terminal = false;
        ans->s = jagged_list;
        return *ans;
    }

    if (strcmp(enustr, "j3list") == 0) {
        ans->is_terminal = false;
        ans->s = j3list;
        return *ans;
    }

    return *ans;
}
char* getSymbol(Symbol symb) {
    //printf("Symbol variable \n");
    switch (symb.s) {
    case (AND):
        return "AND";

    case (ARRAY):
        return "ARRAY";
        
    case (BOOLEAN):
        return "BOOLEAN";

    case (COLON):
        return "COLON";

    case (CONST):
        return "CONST";

    case (CURLYCLOSE):
        return "CURLYCLOSE";

    case (CURLYOPEN):
        return "CURLYOPEN";

    case (DECLARE):
        return "DECLARE";

    case (DIV):
        return "DIV";

    case (ELIPSIS):
        return "ELIPSIS";

    case (EQUALS):
        return "EQUALS";

    case (FALSE):
        return "FALSE";

    case (ID):
        return "ID";

    case (INTEGER):
        return "INTEGER";

    case (JAGGED):
        return "JAGGED";

    case (LIST):
        return "LIST";

    case (LPAREN):
        return "LPAREN";

    case (MINUS):
        return "MINUS";

    case (MULT):
        return "MULT";

    case (OF):
        return "OF";

    case (OR):
        return "OR";

    case (PLUS):
        return "PLUS";

    case (R1):
        return "R1";

    case (REAL):
        return "REAL";

    case (RPAREN):
        return "RPAREN";

    case (SEMICOLON):
        return "SEMICOLON";

    case (SIZE):
        return "SIZE";

    case (SQBC):
        return "SQBC";

    case (SQBO):
        return "SQBO";

    case (TRUE):
        return "TRUE";

    case (VALUES):
        return "VALUES";

    case (VARIABLES):
        return "VARIABLES";

    case (arithmeticexpr):
        return "arithmeticexpr";

    case (array_type):
        return "array_type";

    case (assignment_stmt):
        return "assignment_stmt";

    case (boolexpr):
        return "boolexpr";

    case (code_stmt):
        return "code_stmt";

    case (declaration_stmt):
        return "declaration_stmt";

    case (declaration_type):
        return "declaration_type";

    case (expr):
        return "expr";

    case (fact):
        return "fact";

    case (id_list):
        return "id_list";

    case (index_list):
        return "index_list";

    case (j2list):
        return "j2list";

    case (j3list):
        return "j3list";

    case (jagged2init):
        return "jagged2init";

    case (jagged2list):
        return "jagged2list";

    case (jagged3init):
        return "jagged3init";

    case (jagged3list):
        return "jagged3list";

    case (jagged_array):
        return "jagged_array";

    case (jagged_list):
        return "jagged_list";

    case (list_of_identifiers):
        return "list_of_identifiers";

    case (logfactor):
        return "logfactor";

    case (logterm):
        return "logterm";

    case (main_program):
        return "main_program";

    case (primitive_type):
        return "primitive_type";

    case (program):
        return "program";

    case (range_list):
        return "range_list";

    case (rect_array):
        return "rect_array";

    case (term):
        return "term";

    case (value_list):
        return "value_list";

    case (var):
        return "var";
        toSymbol;
        default:
            return "ERROR!";
    }
    //printf("\tis_terminal : %b\n", symb.is_terminal);
}
