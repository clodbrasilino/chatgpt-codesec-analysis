#include <stdio.h>

typedef struct {
    int x;
    double y;
    char z;
} Tuple;

size_t get_tuple_size(const Tuple *tuple) {
    if (tuple == NULL) {
        return 0;
    }
    return sizeof(*tuple);
}

int main(void) {
    Tuple t = {1, 2.5, 'a'};
    size_t size = get_tuple_size(&t);
    
    if (size > 0) {
        printf("Size of tuple: %zu bytes\n", size);
        printf("Tuple contents: x=%d, y=%.2f, z=%c\n", t.x, t.y, t.z);
    } else {
        fprintf(stderr, "Error: Invalid tuple\n");
        return 1;
    }
    
    return 0;
}