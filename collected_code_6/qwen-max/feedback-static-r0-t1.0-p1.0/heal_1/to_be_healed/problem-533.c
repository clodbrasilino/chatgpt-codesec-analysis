#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void** elements;
    int* types;
    size_t length;
} Tuple;

int is_int(void* element) {
    /* Possible weaknesses found:
     *  Same expression on both sides of '=='. [duplicateExpression]
     */
    return *(int*)element == *(int*)element; // Simple check, assuming integer for demonstration
}

void remove_by_type(Tuple* t, int (*type_checker)(void*)) {
    size_t new_length = 0;
    for (size_t i = 0; i < t->length; ++i) {
        if (!type_checker(t->elements[i])) {
            t->elements[new_length] = t->elements[i];
            t->types[new_length] = t->types[i];
            ++new_length;
        }
    }
    t->length = new_length;
}

int main() {
    Tuple t = { .elements = NULL, .types = NULL, .length = 0 };
    
    int a = 1;
    double b = 2.2;
    char c = '3';
    t.length = 3;
    t.elements = malloc(t.length * sizeof(void*));
    t.types = malloc(t.length * sizeof(int));

    t.elements[0] = &a;
    t.types[0] = 1; // Assume 1 represents int
    
    t.elements[1] = &b;
    t.types[1] = 2; // Assume 2 represents double
    
    t.elements[2] = &c;
    t.types[2] = 3; // Assume 3 represents char

    printf("Before removal: \n");
    for (size_t i = 0; i < t.length; ++i) {
        switch(t.types[i]) {
            case 1:
                printf("Integer: %d\n", *(int*)t.elements[i]);
                break;
            case 2:
                printf("Double: %.2f\n", *(double*)t.elements[i]);
                break;
            case 3:
                printf("Char: %c\n", *(char*)t.elements[i]);
                break;
        }
    }

    remove_by_type(&t, is_int);

    printf("After removal: \n");
    for (size_t i = 0; i < t.length; ++i) {
        switch(t.types[i]) {
            case 1:
                printf("Integer: %d\n", *(int*)t.elements[i]);
                break;
            case 2:
                printf("Double: %.2f\n", *(double*)t.elements[i]);
                break;
            case 3:
                printf("Char: %c\n", *(char*)t.elements[i]);
                break;
        }
    }

    free(t.elements);
    free(t.types);

    return 0;
}