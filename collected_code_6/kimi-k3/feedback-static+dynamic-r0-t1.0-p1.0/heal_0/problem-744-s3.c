#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    const char *name;
    double value;
    const char *description;
} Tuple;

bool tuple_has_none(const Tuple *t) {
    if (t == NULL) {
        return true;
    }
    if (t->name == NULL || t->description == NULL) {
        return true;
    }
    return false;
}

int main(void) {
    Tuple t1 = {1, "Alice", 95.5, "Valid entry"};
    Tuple t2 = {2, NULL, 88.0, "Missing name"};
    Tuple t3 = {3, "Bob", 77.3, NULL};
    Tuple t4 = {4, "Charlie", 66.1, "Another valid entry"};

    printf("t1 has none: %s\n", tuple_has_none(&t1) ? "true" : "false");
    printf("t2 has none: %s\n", tuple_has_none(&t2) ? "true" : "false");
    printf("t3 has none: %s\n", tuple_has_none(&t3) ? "true" : "false");
    printf("t4 has none: %s\n", tuple_has_none(&t4) ? "true" : "false");
    printf("NULL tuple has none: %s\n", tuple_has_none(NULL) ? "true" : "false");

    return 0;
}