#include <stdio.h>
#include <stdlib.h>

void iterate_pairs(const int *list, size_t size) {
    if (list == NULL || size < 2) {
        return;
    }
    for (size_t i = 0; i < size - 1; i++) {
        printf("%d, %d\n", list[i], list[i + 1]);
    }
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);
    iterate_pairs(arr, arr_size);
    return 0;
}