#include <stdlib.h>
#define MAX_CHILD 10
/*
program ( ) {
    DECLARE a OF INTEGER ;
    DECLARE b OF INTEGER ;
    DECLARE c OF INTEGER ;
    a = 5 ;
    b = 2 ;
    c = a + b ;
}
*/

typedef enum {false, true} bool;

typedef struct mock_token {
    char* symbol;
    bool terminal;
    char* name;
} Tok;

typedef struct tn
{
    Tok* data;
    int num_child;
    struct tn *child[MAX_CHILD];
} Tree;

Tree* node(Tok* tok, int num_child) {
    Tree* t = (Tree*)malloc(sizeof(Tree));
    t->data = tok;
    t->num_child = num_child;
    return t;
}

Tok* token(char* symb, bool t, char* n) {
    Tok* tok = (Tok*)malloc(sizeof(Tok));
    tok->symbol = symb;
    tok->terminal = t;
    tok->name = n;
    return tok;
}

int main() {
    Tree* t = (Tree*)malloc(sizeof(Tree));
    Tree *ptr, *ptr1, *ptr2;

    t = node(token("main_program", false, "-"), 6);
    t->child[0] = node(token("PROG", true, "-"), 0);
    t->child[1] = node(token("PAROP", true, "-"), 0);
    t->child[2] = node(token("PARCL", true, "-"), 0);
    t->child[3] = node(token("CUROP", true, "-"), 0);
    t->child[4] = node(token("stmts", false, "-"), 3);
    t->child[5] = node(token("CURCL", true, "-"), 0);


    ptr = t->child[4];

    ptr->child[0] = node(token("stmt", false, "-"), 4);
    ptr->child[1] = node(token("SEMICOL", true, "-"), 0);
    ptr->child[2] = node(token("stmts", false, "-"), 3);


    ptr1 = ptr->child[0], ptr2 = ptr->child[2];

    ptr1->child[0] = node(token("DECLARE", true, "-"), 4);
    ptr1->child[1] = node(token("ID", true, "a"), 0);
    ptr1->child[2] = node(token("OF", true, "-"), 0);
    ptr1->child[3] = node(token("INTEGER", true, "-"), 0);

    ptr2->child[0] = node(token("stmt", false, "-"), 4);
    ptr2->child[1] = node(token("SEMICOL", true, "-"), 0);
    ptr2->child[2] = node(token("stmts", false, "-"), 3);


    ptr1 = ptr2->child[0], ptr2 = ptr2->child[2];

    ptr1->child[0] = node(token("DECLARE", true, "-"), 4);
    ptr1->child[1] = node(token("ID", true, "b"), 0);
    ptr1->child[2] = node(token("OF", true, "-"), 0);
    ptr1->child[3] = node(token("INTEGER", true, "-"), 0);

    ptr2->child[0] = node(token("stmt", false, "-"), 4);
    ptr2->child[1] = node(token("SEMICOL", true, "-"), 0);
    ptr2->child[2] = node(token("stmts", false, "-"), 3);


    ptr1 = ptr2->child[0], ptr2 = ptr2->child[2];

    ptr1->child[0] = node(token("DECLARE", true, "-"), 4);
    ptr1->child[1] = node(token("ID", true, "c"), 0);
    ptr1->child[2] = node(token("OF", true, "-"), 0);
    ptr1->child[3] = node(token("INTEGER", true, "-"), 0);

    ptr2->child[0] = node(token("stmt", false, "-"), 3);
    ptr2->child[1] = node(token("SEMICOL", true, "-"), 0);
    ptr2->child[2] = node(token("stmts", false, "-"), 3);


    ptr1 = ptr2->child[0], ptr2 = ptr2->child[2];

    ptr1->child[0] = node(token("ID", true, "a"), 4);
    ptr1->child[1] = node(token("EQUAL", true, "-"), 0);
    ptr1->child[2] = node(token("CONST", true, "5"), 0);

    ptr2->child[0] = node(token("stmt", false, "-"), 3);
    ptr2->child[1] = node(token("SEMICOL", true, "-"), 0);
    ptr2->child[2] = node(token("stmts", false, "-"), 3);


    ptr1 = ptr2->child[0], ptr2 = ptr2->child[2];

    ptr1->child[0] = node(token("ID", true, "b"), 4);
    ptr1->child[1] = node(token("EQUAL", true, "-"), 0);
    ptr1->child[2] = node(token("CONST", true, "2"), 0);

    ptr2->child[0] = node(token("stmt", false, "-"), 3);
    ptr2->child[1] = node(token("SEMICOL", true, "-"), 0);
    ptr2->child[2] = node(token("stmts", false, "-"), 1);


    ptr1 = ptr2->child[0], ptr2 = ptr2->child[2];

    ptr1->child[0] = node(token("ID", true, "c"), 4);
    ptr1->child[1] = node(token("EQUAL", true, "-"), 0);
    ptr1->child[2] = node(token("expr", false, "-"), 3);

    ptr2->child[0] = node(token("EPSILON", true, "-"), 0);


    ptr1 = ptr1->child[2];

    ptr1->child[0] = node(token("ID", true, "a"), 4);
    ptr1->child[1] = node(token("PLUS", true, "-"), 0);
    ptr1->child[2] = node(token("ID", true, "b"), 0);
}
