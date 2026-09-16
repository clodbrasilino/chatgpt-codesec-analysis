#include <stdio.h>
#include <stdlib.h>

void exchange_n_th_values(int *list, size_t size, size_t n) {
    if (list == NULL || size == 0 || n == 0) {
        return;
    }

    size_t end = (size / n) * n;
    
    for (size_t i = n - 1; i + 1 < end; i += n) {
        int temp = list[i];
        list[i] = list[i + 1];
        list[i + 1] = temp;
    }
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t n = 3;

    printf("Original list: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    exchange_n_th_values(list, size, n);

    printf("Modified list: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    return 0;
}