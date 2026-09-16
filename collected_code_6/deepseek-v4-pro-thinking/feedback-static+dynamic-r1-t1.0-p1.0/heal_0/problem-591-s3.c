#include <stddef.h>
#include <stdio.h>

int interchange_first_last(int *list, size_t size) {
    if (list == NULL || size < 2) {
        return -1;
    }

    int temp = list[0];
    list[0] = list[size - 1];
    list[size - 1] = temp;

    return 0;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    if (interchange_first_last(numbers, size) != 0) {
        return 1;
    }

    for (size_t i = 0; i < size; ++i) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}