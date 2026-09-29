#include <stdio.h>
#include <stdlib.h>

size_t count_odd_elements(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = sizeof(list) / sizeof(list[0]);

    size_t odd_count = count_odd_elements(list, size);

    printf("%zu\n", odd_count);

    size_t null_count = count_odd_elements(NULL, size);
    printf("%zu\n", null_count);

    return 0;
}