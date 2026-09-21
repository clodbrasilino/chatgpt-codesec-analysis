#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_SIZE 50

typedef struct {
    int id;
    char name[NAME_SIZE];
    float score;
} Tuple;

bool is_valid_tuple(const Tuple *t) {
    if (t == NULL) {
        return false;
    }
    if (t->id < 0) {
        return false;
    }
    size_t name_len = strnlen(t->name, NAME_SIZE);
    if (name_len == 0 || name_len >= NAME_SIZE) {
        return false;
    }
    if (t->score < 0.0f || t->score > 100.0f) {
        return false;
    }
    return true;
}

bool set_tuple_name(Tuple *t, const char *name) {
    if (t == NULL || name == NULL) {
        return false;
    }
    size_t len = strnlen(name, NAME_SIZE);
    if (len == 0 || len >= NAME_SIZE) {
        return false;
    }
    snprintf(t->name, NAME_SIZE, "%s", name);
    return true;
}

int main(void) {
    Tuple t1 = {1, "", 85.5f};
    Tuple t2 = {-1, "", 150.0f};

    if (!set_tuple_name(&t1, "Alice")) {
        fprintf(stderr, "Failed to set name for t1\n");
        return EXIT_FAILURE;
    }

    if (is_valid_tuple(&t1)) {
        printf("Tuple 1 is valid.\n");
    } else {
        printf("Tuple 1 is invalid.\n");
    }

    if (is_valid_tuple(&t2)) {
        printf("Tuple 2 is valid.\n");
    } else {
        printf("Tuple 2 is invalid.\n");
    }

    return EXIT_SUCCESS;
}