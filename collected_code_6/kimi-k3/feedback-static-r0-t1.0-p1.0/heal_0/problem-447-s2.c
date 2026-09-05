#include <stdio.h>
#include <stdlib.h>

void cube_elements(int *arr, size_t size) {
    size_t i;
    if (arr == NULL) {
        return;
    }
    for (i = 0; i < size; i++) {
        arr[i] = arr[i] * arr[i] * arr[i];
    }
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    size_t i;

    cube_elements(numbers, size);

    for (i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}