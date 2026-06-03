//
// Created by antor on 03.06.2026.
//

#ifndef HW3_STACK_H
#define HW3_STACK_H
#include <stdbool.h>
#include <stddef.h>

struct stack;

typedef void *elem_t;

typedef elem_t (*clone_t) (elem_t e);
typedef void (*destroy_t) (elem_t e);
typedef void (*print_t) (elem_t e);

struct stack* stack_create (
        size_t size,
        clone_t clone_func,
        destroy_t destroy_func,
        print_t print_func);

int stack_destroy(struct stack* stack);
int stack_push(struct stack* stack, elem_t e);
void stack_pop(struct stack* stack);
elem_t stack_peek(struct stack* stack);
size_t stack_size(struct stack* stack);
bool stack_is_empty(struct stack* stack);
size_t stack_capacity(struct stack* stack);
void stack_print(struct stack* stack);

#endif //HW3_STACK_H
