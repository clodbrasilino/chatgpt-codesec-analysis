#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char *name;
} Tuple;

Tuple* create_tuple(int id, const char *name) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    t->id = id;
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strdup'
     *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
     */
    t->name = strdup(name);
    if (t->name == NULL) {
        free(t);
        exit(EXIT_FAILURE);
    }
    return t;
}

int get_initial_data(const Tuple *t) {
    return t->id;
}

const char* get_last_data(const Tuple *t) {
    return t->name;
}

void free_tuple(Tuple *t) {
    free(t->name);
    free(t);
}

int main() {
    Tuple *record = create_tuple(1, "John Doe");
    printf("Initial Data: %d\n", get_initial_data(record));
    printf("Last Data: %s\n", get_last_data(record));
    free_tuple(record);
    return 0;
}