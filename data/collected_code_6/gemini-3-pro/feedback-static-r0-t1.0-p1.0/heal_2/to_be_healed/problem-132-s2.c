#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
} Tuple;

char* tuple_to_string(const Tuple* t) {
    if (t == NULL) {
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
    
    snprintf(t.name, sizeof(t.name), "%s", "Example");

    char* str = tuple_to_string(&t);

    if (str != NULL) {
        printf("%s\n", str);
        free(str);
    }

    return 0;
}