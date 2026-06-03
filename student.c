#include "student.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student *student_t;

void* student_clone(void* e) {
    if (!e) return NULL;

    student_t student = e;

    student_t new_student = malloc(sizeof(struct student));
    if (!new_student) return NULL;

    // allocate new memory for a name line in order to avoid pointing to the same value
    char* name = malloc((strlen(student->name) + 1) * sizeof(char));
    if (!name) {    // failure
        free(new_student);  // free memory allocated for new student in case of failure
        return NULL;
    }
    strcpy(name, student->name);

    new_student->name = name;
    new_student->age = student->age;
    new_student->id = student->id;

    return new_student;
}

void student_destroy(void* e) {
    if (e) {
        student_t student = e;
        free(student->name);
        free(student);
    }
}

void student_print(void* e) {
    if (e) {
        student_t student = e;
        printf("student name: %s, age: %d, id: %d.\n", student->name, student->age, student->id);
    }
}

