#include <stdio.h>

void move_zeroes(int *arr, size_t len) {
    if (arr == NULL || len == 0) {
        return;
    }
    size_t insert_pos = 0;
    for (size_t i = 0; i < len; i++) {
        if (arr[i] != 0) {
            arr[insert_pos] = arr[i];
            insert_pos++;
        }
    }
    while (insert_pos < len) {
        arr[insert_pos] = 0;
        insert_pos++;
    }
}

int main(void) {
    int arr[] = {1, 0, 2, 0, 3, 4, 0, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    move_zeroes(arr, len);
    for (size_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}