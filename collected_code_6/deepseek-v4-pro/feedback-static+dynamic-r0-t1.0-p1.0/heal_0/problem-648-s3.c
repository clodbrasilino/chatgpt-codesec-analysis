#include <stdio.h>
#include <stdlib.h>

void swap_pairs(int *list, int size) {
    for (int i = 0; i < size - 1; i += 2) {
        int temp = list[i];
        list[i] = list[i + 1];
        list[i + 1] = temp;
    }
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(list) / sizeof(list[0]);

    printf("Original list: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    swap_pairs(list, size);

    printf("Modified list: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}