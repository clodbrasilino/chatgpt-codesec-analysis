#include <stdio.h>

size_t remove_negatives(int arr[], size_t size) {
    size_t j = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] >= 0) {
            arr[j] = arr[i];
            j++;
        }
    }
    return j;
}

int main(void) {
    int list[] = {3, -1, 4, -1, 5, -9, 2, -6, 5, 0};
    size_t size = sizeof(list) / sizeof(list[0]);

    size_t new_size = remove_negatives(list, size);

    for (size_t i = 0; i < new_size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}