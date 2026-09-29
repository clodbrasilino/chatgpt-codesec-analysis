#include <stdio.h>
#include <stdlib.h>

void print_int(int value) {
    printf("%d ", value);
}

void print_n_times(void (*func)(int), int *array, size_t size, int n) {
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < size; j++) {
            func(array[j]);
        }
        printf("\n");
    }
}

int main(void) {
    int array[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(array) / sizeof(array[0]);
    int n = 3;

    print_n_times(print_int, array, size, n);

    return 0;
}