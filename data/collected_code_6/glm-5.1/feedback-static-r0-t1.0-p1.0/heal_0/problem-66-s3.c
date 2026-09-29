#include <stdio.h>
#include <stdlib.h>

size_t count_positive(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            ++count;
        }
    }
    return count;
}

int main(void) {
    int list[] = {-3, 5, 0, 12, -8, 7, 0, -1, 4};
    size_t size = sizeof(list) / sizeof(list[0]);

    size_t positive_count = count_positive(list, size);

    printf("%zu\n", positive_count);

    return EXIT_SUCCESS;
}