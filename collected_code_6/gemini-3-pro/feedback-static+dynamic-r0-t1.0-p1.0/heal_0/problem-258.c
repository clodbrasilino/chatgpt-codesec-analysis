#include <stdio.h>
#include <stdlib.h>

size_t count_odd_elements(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    size_t odd_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            odd_count++;
        }
    }
    
    return odd_count;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(list) / sizeof(list[0]);

    size_t odd_count = count_odd_elements(list, size);

    printf("Number of odd elements: %zu\n", odd_count);

    return 0;
}