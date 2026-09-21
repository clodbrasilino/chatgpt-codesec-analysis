#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    char *name;
} Tuple;

char* tuple_to_string(const Tuple* t) {
    if (t == NULL || t->name == NULL) {
        return NULL;
    }

    size_t size = snprintf(NULL, 0, "(%d, %.2f, %s)", t->id, t->value, t->name) + 1;
    char* str = (char*)malloc(size);

    if (str != NULL) {
        snprintf(str, size, "(%d, %.2f, %s)", t->id, t->value, t->name);
    }

    return str;
}

int main(void) {
    Tuple t;
    t.id = 1;
    t.value = 3.14;
    
    const char example_name[] = "Example";
    size_t name_len = sizeof(example_name);
    
    t.name = (char*)malloc(name_len);
    if (t.name == NULL) {
        return 1;
    }
    
    snprintf(t.name, name_len, "%s", example_name);

    char* str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    free(t.name);

    return 0;
}