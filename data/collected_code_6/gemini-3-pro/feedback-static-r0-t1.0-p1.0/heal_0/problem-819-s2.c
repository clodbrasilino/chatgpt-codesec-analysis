#include <stdio.h>
#include <stdlib.h>

void count_consecutive_duplicates(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return;
    }

    int current_element = array[0];
    size_t count = 1;

    for (size_t i = 1; i < size; ++i) {
        if (array[i] == current_element) {
            count++;
        } else {
            printf("%d occurred %zu times continuously\n", current_element, count);
            current_element = array[i];
            count = 1;
        }
    }
    printf("%d occurred %zu times continuously\n", current_element, count);
}

int main(void) {
    int arr[] = {1, 1, 1, 2, 3, 3, 4, 1, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    count_consecutive_duplicates(arr, size);

    return 0;
}