#include <stdio.h>
#include <stdlib.h>

size_t count_even_elements(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    size_t even_count = count_even_elements(numbers, size);

    printf("Number of even elements: %zu\n", even_count);

    return EXIT_SUCCESS;
}