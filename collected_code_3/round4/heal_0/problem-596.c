#include <stdio.h>

typedef struct {
    int a;
    double b;
    char c;
} Tuple;

size_t get_tuple_size(Tuple *tuple) {
    return sizeof(*tuple);
}

int main() {
    Tuple tuple = {1, 2.0, 'a'};
    printf("Size of tuple: %zu bytes\n", get_tuple_size(&tuple));
    return 0;
}