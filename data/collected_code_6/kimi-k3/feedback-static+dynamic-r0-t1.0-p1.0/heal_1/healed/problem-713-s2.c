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
    if (strnlen(t->name, NAME_SIZE) == 0 || strnlen(t->name, NAME_SIZE) >= NAME_SIZE) {
        return false;
    }
    if (t->score < 0.0f || t->score > 100.0f) {
        return false;
    }
    return true;
}

int main(void) {
    Tuple t1 = {1, "Alice", 85.5f};
    Tuple t2 = {-1, "", 150.0f};

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

    return 0;
}