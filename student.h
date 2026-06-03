#ifndef HW3_STUDENT_H
#define HW3_STUDENT_H

struct student {
    char *name;
    int age;
    int id;
};

void* student_clone(void* e);
void student_destroy(void*e);
void student_print(void* e);

#endif //HW3_STUDENT_H
