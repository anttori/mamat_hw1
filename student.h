#ifndef HW3_STUDENT_H
#define HW3_STUDENT_H

#include "stack.h"

struct student {
    char *name;
    int age;
    int id;
};

elem_t student_clone(elem_t e);
void student_destroy(elem_t e);
void student_print(elem_t e);

#endif //HW3_STUDENT_H
