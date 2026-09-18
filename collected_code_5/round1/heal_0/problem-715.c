#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tuple {
    int* elements;
    int size;
} Tuple;

Tuple* string_to_tuple(const char* string) {
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ',') {
            count++;
        }
    }

    Tuple* t = (Tuple*) malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->elements = (int*) malloc(sizeof(int) * (count + 1));
    if (t->elements == NULL) {
        free(t);
        return NULL;
    }
    t->size = count + 1;

    const char* str_ptr = string;
    for (int i = 0; i < t->size; i++) {
        t->elements[i] = atoi(str_ptr);
        while (*str_ptr != '\0' && *str_ptr != ',') {
            str_ptr++;
        }
        if (*str_ptr == ',') {
            str_ptr++;
        }
    }

    return t;
}

void free_tuple(Tuple* t) {
    free(t->elements);
    free(t);
}

int main() {
    const char* str = "1,2,3,4,5";
    Tuple* t = string_to_tuple(str);

    if(t != NULL) {
        for (int i = 0; i < t->size; i++) {
            printf("%d ", t->elements[i]);
        }

        printf("\n");
        free_tuple(t); 
    } else {
        printf("Failed to convert string to tuple.\n");
    }

    return 0;
}