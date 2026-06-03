#include <stddef.h>
#include "stack.h"

#include <stdlib.h>

    // FIX FAILURE RETURN VALUES

struct stack {
    size_t size;    // max elements count
    size_t elem_count;    // current elements count

    elem_t* elements;   // array to store the elements

    // user provided functions
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;
};

struct stack* stack_create (
        size_t size,
        clone_t clone_func,
        destroy_t destroy_func,
        print_t print_func) {

    struct stack* new_stack = malloc(sizeof(struct stack));
    if (!new_stack) return NULL;    // memory allocation failure

    elem_t* elements = malloc(size * sizeof(elem_t));
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

int stack_destroy(struct stack* stack) {
    if (stack) {
        for (int i = 0; i <= stack->size; i++) {    // destroy each element with user provided function
            stack->destroy_func(*(stack->elements + i));
        }
        free(stack->elements);
        free(stack);

        return 0;   // success
    }

    return -1;  // failure
}

int stack_push(struct stack* stack, elem_t e) {
    if (stack && (stack->elem_count < stack->size) ) {
        elem_t e_clone = stack->clone_func(e);
        if (!e_clone) return -1;    // clone failure

        *(stack->elements + stack->elem_count++) = e_clone;

        return 0;
    }

    return -1;
}

void stack_pop(struct stack* stack) {
    if (stack && stack->elem_count > 0) {
        stack->elem_count--;
        stack->destroy_func(*(stack->elements + stack->elem_count));
    }
}

elem_t stack_peek(struct stack* stack) {
    if (stack && stack->elem_count > 0) {
        return *(stack->elements + stack->elem_count - 1);
    }

    return NULL;
}

size_t stack_size(struct stack* stack) {
    if (stack) return stack->elem_count;
    return 0;
}

bool stack_is_empty(struct stack* stack) {
    if (stack) return stack->elem_count == 0;
    return false;
}

size_t stack_capacity(struct stack* stack) {
    if (stack) return stack->size - stack->elem_count;
    return 0;
}

void stack_print(struct stack* stack) {
    if (stack && stack->elem_count > 0) {
        for (int i = stack->elem_count - 1; i >= 0; i--) {
            stack->print_func(*(stack->elements + i));
        }
    }
}
