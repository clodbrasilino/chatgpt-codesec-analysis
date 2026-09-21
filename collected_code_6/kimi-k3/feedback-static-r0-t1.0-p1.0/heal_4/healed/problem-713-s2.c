#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    float score;
} Tuple;

bool is_valid_tuple(const Tuple *t) {
    if (t == NULL) {
        return false;
    }
    if (t->id < 0) {
        return false;
    }
    if (strnlen(t->name, MAX_NAME_LEN) == 0) {
        return false;
    }
    if (t->name[MAX_NAME_LEN - 1] != '\0') {
        return false;
    }
    if (t->score < 0.0f || t->score > 100.0f) {
        return false;
    }
    return true;
}

bool init_tuple(Tuple *t, int id, const char *name, float score) {
    if (t == NULL || name == NULL) {
        return false;
    }
    if (id < 0) {
        return false;
    }
    size_t name_len = strnlen(name, MAX_NAME_LEN);
    if (name_len == 0 || name_len >= MAX_NAME_LEN) {
        return false;
    }
    if (score < 0.0f || score > 100.0f) {
        return false;
    }
    t->id = id;
    snprintf(t->name, MAX_NAME_LEN, "%s", name);
    t->score = score;
    return true;
}

int main(void) {
    Tuple t1 = {0};
    Tuple t2 = {0};

    if (!init_tuple(&t1, 1, "Alice", 85.5f)) {
        fprintf(stderr, "Failed to initialize tuple 1\n");
        return EXIT_FAILURE;
    }

    if (!init_tuple(&t2, -1, "", 150.0f)) {
        fprintf(stderr, "Failed to initialize tuple 2\n");
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