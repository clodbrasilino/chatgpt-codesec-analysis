#include <stdio.h>
#include <stdlib.h>

int* find_divisible(const int* list, int size, int m, int n, int* result_size) {
    if (list == NULL || result_size == NULL || size <= 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % m == 0 || list[i] % n == 0) {
            count++;
        }
    }

    if (count == 0) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % m == 0 || list[i] % n == 0) {
            result[index++] = list[i];
        }
    }

    *result_size = count;
    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20, 25, 30};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    int result_size = 0;
    
    int* result = find_divisible(numbers, size, m, n, &result_size);
    
    if (result == NULL && result_size > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Numbers divisible by %d or %d: ", m, n);
    if (result == NULL) {
        printf("none\n");
    } else {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }
    
    return 0;
}