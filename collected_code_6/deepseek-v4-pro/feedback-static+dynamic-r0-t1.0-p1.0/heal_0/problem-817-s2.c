#include <stdio.h>
#include <stdlib.h>

int *find_divisible(int *list, int size, int m, int n, int *result_size) {
    int *result = (int *)malloc(size * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % m == 0 || list[i] % n == 0) {
            result[count++] = list[i];
        }
    }
    *result_size = count;
    return result;
}

int main(void) {
    int list[] = {10, 15, 20, 25, 30, 35, 40, 45, 50};
    int size = sizeof(list) / sizeof(list[0]);
    int m = 2;
    int n = 3;
    int result_size = 0;
    int *result = find_divisible(list, size, m, n, &result_size);
    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}