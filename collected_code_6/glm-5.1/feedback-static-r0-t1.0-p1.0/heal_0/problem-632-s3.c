#include <stdio.h>
#include <stdlib.h>

void move_zeroes(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return;
    }

    size_t insert_pos = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] != 0) {
            list[insert_pos] = list[i];
            insert_pos++;
        }
    }

    for (size_t i = insert_pos; i < size; i++) {
        list[i] = 0;
    }
}

int main(void) {
    int list[] = {1, 0, 2, 0, 3, 4, 0, 5};
    size_t size = sizeof(list) / sizeof(list[0]);

    move_zeroes(list, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}