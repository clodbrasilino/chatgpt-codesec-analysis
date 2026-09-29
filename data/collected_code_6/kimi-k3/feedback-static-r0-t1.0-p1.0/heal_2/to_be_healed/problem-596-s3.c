#include <stdio.h>
#include <string.h>

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

void tuple_init(Tuple *t, int id, double value, const char *label) {
    if (t == NULL) {
        return;
    }
    t->id = id;
    t->value = value;
    if (label != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(t->label, label, sizeof(t->label) - 1);
        t->label[sizeof(t->label) - 1] = '\0';
    } else {
        t->label[0] = '\0';
    }
}

int main(void) {
    Tuple t;
    tuple_init(&t, 1, 3.14, "example");
    size_t size = tuple_size(&t);
    if (size > 0) {
        printf("%d %.2f %s %zu\n", t.id, t.value, t.label, size);
    }
    return 0;
}