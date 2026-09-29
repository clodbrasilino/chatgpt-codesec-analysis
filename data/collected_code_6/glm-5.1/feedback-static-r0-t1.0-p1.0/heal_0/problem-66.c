#include <stdio.h>
#include <stdlib.h>

size_t count_positive(const int *list, size_t size) {
    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    int data[] = {5, -2, 0, 7, 1, -8, 3};
    size_t size = sizeof(data) / sizeof(data[0]);
    size_t positive_count = count_positive(data, size);
    printf("%zu\n", positive_count);
    return 0;
}