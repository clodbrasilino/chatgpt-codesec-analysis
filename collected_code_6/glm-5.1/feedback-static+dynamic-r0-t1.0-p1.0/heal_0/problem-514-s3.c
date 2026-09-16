#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sum_tuple_elements(Tuple *list, size_t size) {
    int sum = 0;
    if (list == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (__builtin_add_overflow(sum, list[i].a, &sum)) {
            return 0;
        }
        if (__builtin_add_overflow(sum, list[i].b, &sum)) {
            return 0;
        }
    }
    return sum;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t size = sizeof(list) / sizeof(list[0]);
    int result = sum_tuple_elements(list, size);
    printf("%d\n", result);
    return 0;
}