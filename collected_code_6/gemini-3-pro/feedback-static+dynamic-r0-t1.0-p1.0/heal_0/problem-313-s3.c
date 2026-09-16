#include <stdio.h>
#include <stdlib.h>

void print_positive_numbers(const int *list, size_t size) {
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int numbers[] = {-5, 3, -1, 0, 7, -9, 12, 4};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    print_positive_numbers(numbers, size);

    return 0;
}