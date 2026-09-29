#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int id;
    double value;
    char label[64];
} Tuple;

size_t tuple_size(const Tuple *t) {
    if (t == NULL) {
        return 0;
    }
    return sizeof(*t);
}

int set_label(Tuple *t, const char *src) {
    if (t == NULL || src == NULL) {
        return -1;
    }

    size_t max_len = sizeof(t->label) - 1;
    size_t src_len = strnlen(src, max_len);
    
    if (src_len > max_len) {
        return -1;
    }

    memcpy(t->label, src, src_len);
    t->label[src_len] = '\0';
    
    return 0;
}

int main(void) {
    Tuple t = {1, 3.14, ""};

    if (set_label(&t, "example") != 0) {
        fprintf(stderr, "Failed to set label\n");
        return EXIT_FAILURE;
    }

    size_t size = tuple_size(&t);
    if (size > 0) {
        printf("%zu\n", size);
        printf("ID: %d, Value: %.2f, Label: %s\n", t.id, t.value, t.label);
    }
    
    return EXIT_SUCCESS;
}