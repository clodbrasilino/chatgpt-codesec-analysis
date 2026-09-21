#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int id;
    double value;
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
        size_t label_len = strlen(label);
        size_t copy_len = label_len < sizeof(t->label) - 1 ? label_len : sizeof(t->label) - 1;
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