#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int find_max_element(Tuple *records, size_t count) {
    if (records == NULL || count == 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    int max_val = records[0].a;
    for (size_t i = 0; i < count; i++) {
        if (records[i].a > max_val) {
            max_val = records[i].a;
        }
        if (records[i].b > max_val) {
            max_val = records[i].b;
        }
    }

    return max_val;
}

int main(void) {
    Tuple records[] = {{3, 7}, {1, 9}, {4, 2}, {8, 5}};
    size_t count = sizeof(records) / sizeof(records[0]);

    int max = find_max_element(records, count);
    printf("%d\n", max);

    return 0;
}