#include <stdio.h>
#include <stdlib.h>

void find_even_numbers(const int *list, int n, int **even_list, int *even_count) {
    *even_count = 0;
    for (int i = 0; i < n; ++i) {
        if (list[i] % 2 == 0) {
            (*even_count)++;
        }
    }

    *even_list = malloc((*even_count) * sizeof(int));
    if (*even_list == NULL) {
        return;
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (list[i] % 2 == 0) {
            (*even_list)[index++] = list[i];
        }
    }
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int *even_numbers;
    int even_count;

    find_even_numbers(numbers, n, &even_numbers, &even_count);

    for (int i = 0; i < even_count; ++i) {
        printf("%d ", even_numbers[i]);
    }
    printf("\n");

    free(even_numbers);
    return 0;
}