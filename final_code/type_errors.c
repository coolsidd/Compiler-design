#include "./type_errors.h"


void printErrors(ErrorNode* err) {
    printf( "|%5s|%10s|%10s|%10s|%10s|%10s|%10s|%5s|%20s|\n",
            "num", "stmt type", "operator", "lexeme 1", "type 1",
            "lexeme 2", "type 2", "depth", "error message");

    while (err != NULL) {
        printf( "|%5d|%10s|%10s|%10s|%10s|%10s|%10s|%5d|%20s|\n",
                err->line_num, err->stmt_type, err->op, err->lex1, err->type1,
                err->lex2, err->type2,  err->depth, err->message);
        err = err->next;
    }
}

ErrorNode* add_error( ErrorNode* err,
                char* lex1, char* type1, char* lex2, char* type2,
                int ln, int depth, char* stmt_type, char* op, char* message) {

    ErrorNode* newerr = (ErrorNode*)malloc(sizeof(ErrorNode));
    newerr->lex1 = lex1;
    newerr->lex2 = lex2;
    newerr->type1 = type1;
    newerr->type2 = type2;
    newerr->line_num = ln;
    newerr->depth = depth;
    newerr->stmt_type = stmt_type;
    newerr->op = op;
    newerr->message = message;

    if (!err) {
        err = newerr;
    } else {
        err->next = newerr;
        err = newerr;
    }

    return err;
}

void destroy_err(ErrorNode* err) {
   ErrorNode* tmp;
   while (err != NULL) {
       tmp = err;
       err = err->next;
       free(tmp);
    }
}
