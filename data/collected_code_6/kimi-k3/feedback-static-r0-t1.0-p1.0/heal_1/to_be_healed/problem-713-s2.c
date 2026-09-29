#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    float score;
} Tuple;

bool is_valid_tuple(const Tuple *t) {
    if (t == NULL) {
        return false;
    }
    if (t->id < 0) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(t->name) == 0) {
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