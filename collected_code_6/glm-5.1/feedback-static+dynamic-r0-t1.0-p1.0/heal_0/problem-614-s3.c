#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int cumulative_sum(Tuple *list, size_t size) {
    int sum = 0;
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        sum += list[i].a;
        sum += list[i].b;
    }
    return sum;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t size = sizeof(list) / sizeof(list[0]);
    int sum = cumulative_sum(list, size);
    printf("%d\n", sum);
    return 0;
}