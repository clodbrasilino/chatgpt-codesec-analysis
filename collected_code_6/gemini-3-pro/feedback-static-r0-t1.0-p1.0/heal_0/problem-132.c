#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    char name[20];
} Tuple;

char* tuple_to_string(const Tuple* t) {
    if (t == NULL) {
        return NULL;
    }

    size_t needed_size = snprintf(NULL, 0, "(%d, %.2f, %s)", t->id, t->value, t->name) + 1;
    
    char* str = (char*)malloc(needed_size);
    if (str == NULL) {
        return NULL;
    }

    snprintf(str, needed_size, "(%d, %.2f, %s)", t->id, t->value, t->name);
    
    return str;
}

int main(void) {
    Tuple t = {1, 99.50, "C-Language"};
    
    char* str = tuple_to_string(&t);
    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}