#ifndef HW3_STACK_H
#define HW3_STACK_H
#include <stdbool.h>
#include <stddef.h>

#define SUCCESS 0
#define ERROR 1

struct stack;

typedef void *elem_t;

// user provided functions
typedef elem_t (*clone_t) (elem_t e);
typedef void (*destroy_t) (elem_t e);
typedef void (*print_t) (elem_t e);

/*
Input: size, user proved functions. Output: new stack instance
Creates new stack instance using provided arguments
*/
struct stack* stack_create (
        size_t size,
        clone_t clone_func,
        destroy_t destroy_func,
        print_t print_func);

// frees allocated memory of provided stack
int stack_destroy(struct stack* stack);

// adds provided element to provided stack
int stack_push(struct stack* stack, elem_t e);

// removes last entered element from provided stack
void stack_pop(struct stack* stack);

// returns pointer to last entered element of provided stack
elem_t stack_peek(struct stack* stack);

// returns provided stack elements count
size_t stack_size(struct stack* stack);

// returns if provided stack has no elements
bool stack_is_empty(struct stack* stack);

// return if there is space left for new elements in a provided stack
size_t stack_capacity(struct stack* stack);

// prints provided stack elements starting from last entered element
void stack_print(struct stack* stack);

#endif //HW3_STACK_H
