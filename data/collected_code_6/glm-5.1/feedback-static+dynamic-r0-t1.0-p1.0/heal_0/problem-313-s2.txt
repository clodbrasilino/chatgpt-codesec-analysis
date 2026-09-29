#include <stdio.h>
#include <stdlib.h>

void print_positive_numbers(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (list[i] > 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int list[] = {3, -1, 4, -1, 5, -9, 2, -6, 5, 3, 0};
    size_t size = sizeof(list) / sizeof(list[0]);

    print_positive_numbers(list, size);

    return 0;
}