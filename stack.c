#include <stddef.h>
#include "stack.h"

#include <stdlib.h>


struct stack {
    size_t size;    // max elements count
    size_t elem_count;    // current elements count

    elem_t* elements;   // array to store the elements

    // user provided functions
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;
};

/*
Input: size, user proved functions. Output: new stack instance
Creates new stack instance using provided arguments
*/
struct stack* stack_create (
        size_t size,
        clone_t clone_func,
        destroy_t destroy_func,
        print_t print_func) {

    struct stack* new_stack = malloc(sizeof(struct stack));		// malloc for a new stack instance
    if (!new_stack) return NULL;    // memory allocation failure

    elem_t* elements = malloc(size * sizeof(elem_t));	// malloc for a stack elements array
    if (!elements) {
        free(new_stack);    // free memory allocated for new_stack in case of failure
        return NULL;     // memory allocation failure
    }

    new_stack->size = size;
    new_stack->elem_count = 0;
    new_stack->elements = elements;

    new_stack->clone_func = clone_func;
    new_stack->destroy_func = destroy_func;
    new_stack->print_func = print_func;

    return new_stack;
}

// frees allocated memory of provided stack
int stack_destroy(struct stack* stack) {
    if (stack) {
        for (int i = 0; i <= stack->size; i++) {    // destroy each array element using user provided function
            stack->destroy_func(*(stack->elements + i));
        }
        
        free(stack->elements);
        free(stack);

        return SUCCESS;   // success
    }
    
    return ERROR;	// error
}

// adds provided element to provided stack
int stack_push(struct stack* stack, elem_t e) {
    if (stack && (stack->elem_count < stack->size) ) {
    
        elem_t e_clone = stack->clone_func(e);	// create copy of provided element
        if (!e_clone) return ERROR;    // clone failure

        *(stack->elements + stack->elem_count++) = e_clone;		// put new element copy into array and increment elements count
        
        return SUCCESS;		// success
    }
    
    return ERROR;	// error
}

// removes last entered element from provided stack
void stack_pop(struct stack* stack) {
    if (stack && stack->elem_count > 0) {
        stack->elem_count--;	// decrement elements count
        stack->destroy_func(*(stack->elements + stack->elem_count));	// destroy last entered element with user provided function
    }
}

// returns pointer to last entered element of provided stack
elem_t stack_peek(struct stack* stack) {
    if (stack && stack->elem_count > 0) {
        return *(stack->elements + stack->elem_count - 1);	
    }

    return NULL;
}

// returns provided stack elements count
size_t stack_size(struct stack* stack) {
    if (stack) return stack->elem_count;
    return 0;	// error (returning 0 according to task requirement)
}

// returns if provided stack has no elements
bool stack_is_empty(struct stack* stack) {
    if (stack) return stack->elem_count == 0;
    return false;	// error
}

// return if there is space left for new elements in a provided stack
size_t stack_capacity(struct stack* stack) {
    if (stack) return stack->size - stack->elem_count;
    return 0;   // error (returning 0 according to task requirement)
}

// prints provided stack elements starting from last entered element
void stack_print(struct stack* stack) {
    if (stack && stack->elem_count > 0) {
        for (int i = stack->elem_count - 1; i >= 0; i--) {	// run a loop with decrementing counter 
            stack->print_func(*(stack->elements + i));		// print array elements in a descending order
        }
    }
}
