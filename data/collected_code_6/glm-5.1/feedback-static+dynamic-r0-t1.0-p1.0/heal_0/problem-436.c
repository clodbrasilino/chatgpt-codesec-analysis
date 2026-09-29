#include <stdio.h>
#include <stdlib.h>

void print_negative_numbers(const int *list, size_t size) {
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int list[] = {5, -2, 0, -7, 3, -1, 8};
    size_t size = sizeof(list) / sizeof(list[0]);

    print_negative_numbers(list, size);

    return 0;
}