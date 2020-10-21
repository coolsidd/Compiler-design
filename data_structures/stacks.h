#include<stdlib.h>
typedef struct ____STACK_NODE____ stack_node;

// Defines structure of each node of a stack DS
struct ____STACK_NODE____
{
    void *data;
    stack_node *next;
};

typedef struct ____STACK____ stack;

// Defines structure of Stack DS
struct ____STACK____
{
    stack_node *top;
    int num_elements;
};

// Creates a new empty stack and returns the pointer to stack
stack *create_stack();

// Pushes an element into the stack
void push(stack *s, void *data);

// Returns the topmost element of the stack without removing it
void *top(stack *s);

// Pops and element from the stack
void *pop(stack *s);

// Returns the number of elements in the stack
int stack_size(stack *s);

// Destroys the stack
void destroy_nonempty_stack(stack *s);