#ifndef HW3_STUDENT_H
#define HW3_STUDENT_H

struct student {
    char *name;
    int age;
    int id;
};

/*
Input: struct student object. Output: struct student object
Creates new student instance and copies provided element into it
*/
void* student_clone(void* e);

/*
Input: struct student object. No output
Frees memory for all student fields including name line
*/
void student_destroy(void*e);

/*
Input: struct student object. No output
Prints provided student fields in a declared format (declared in hw3 instructions)
*/
void student_print(void* e);

#endif //HW3_STUDENT_H
