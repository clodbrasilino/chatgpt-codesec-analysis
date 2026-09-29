#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    double value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char label[32];
} Tuple;

size_t tuple_size(const Tuple *t) {
    if (t == NULL) {
        return 0;
    }
    return sizeof(*t);
}

bool tuple_init(Tuple *t, int id, double value, const char *label) {
    if (t == NULL) {
        return false;
    }
    t->id = id;
    t->value = value;
    if (label != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t label_len = strlen(label);
        size_t copy_len = label_len < sizeof(t->label) - 1 ? label_len : sizeof(t->label) - 1;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->label, label, copy_len);
        t->label[copy_len] = '\0';
    } else {
        t->label[0] = '\0';
    }
    return true;
}

int main(void) {
    Tuple t;
    if (!tuple_init(&t, 1, 3.14, "example")) {
        return 1;
    }
    size_t size = tuple_size(&t);
    if (size > 0) {
        printf("%d %.2f %s %zu\n", t.id, t.value, t.label, size);
    }
    return 0;
}