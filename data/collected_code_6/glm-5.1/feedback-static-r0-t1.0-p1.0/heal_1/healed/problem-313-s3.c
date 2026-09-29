#include <stdio.h>
#include <stdlib.h>

void print_positive_numbers(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] > 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int data[] = {-5, 10, 0, 42, -8, 3};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    print_positive_numbers(data, data_size);

    return 0;
}