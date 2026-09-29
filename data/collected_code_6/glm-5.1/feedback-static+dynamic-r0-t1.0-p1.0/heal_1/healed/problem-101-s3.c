#include <stdio.h>
#include <stdlib.h>

int find_kth_sum(const int *array, size_t size, size_t k) {
    if (array == NULL) {
        fprintf(stderr, "Invalid array pointer\n");
        exit(EXIT_FAILURE);
    }
    if (k > size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
    int sum = 0;
    for (size_t i = 0; i < k; i++) {
        sum += array[i];
    }
    return sum;
}

int main(void) {
    int array[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(array) / sizeof(array[0]);
    int result1 = find_kth_sum(array, size, 4);
    int result2 = find_kth_sum(array, size, 5);
    printf("%d\n%d\n", result1, result2);
    return 0;
}