#include <stdio.h>
#include <string.h>

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

int main(void) {
    Tuple t = {1, 3.14, "example"};
    size_t size = tuple_size(&t);
    if (size > 0) {
        printf("ID: %d, Value: %.2f, Label: %s, Size: %zu\n", t.id, t.value, t.label, size);
    }
    return 0;
}