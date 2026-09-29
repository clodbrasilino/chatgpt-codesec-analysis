#include <stdio.h>
#include <stddef.h>

void remove_odd(int *list, size_t *size) {
    if (size == NULL) {
        return;
    }

    if (list == NULL) {
        *size = 0;
        return;
    }

    size_t write_index = 0;

    for (size_t read_index = 0; read_index < *size; ++read_index) {
        if (list[read_index] % 2 == 0) {
            list[write_index] = list[read_index];
            ++write_index;
        }
    }

    *size = write_index;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    remove_odd(numbers, &count);

    for (size_t i = 0; i < count; ++i) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}