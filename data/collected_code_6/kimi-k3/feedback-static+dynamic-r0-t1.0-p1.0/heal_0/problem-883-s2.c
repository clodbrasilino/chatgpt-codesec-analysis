#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int find_divisible(const int *numbers, size_t count, int m, int n, int **result, size_t *result_count)
{
    size_t i;
    size_t found = 0;
    int *temp;

    if (numbers == NULL || result == NULL || result_count == NULL || m == 0 || n == 0) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (count == 0) {
        return 0;
    }

    temp = malloc(count * sizeof(int));
    if (temp == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            temp[found] = numbers[i];
            found++;
        }
    }

    if (found == 0) {
        free(temp);
        return 0;
    }

    *result = temp;
    *result_count = found;
    return 0;
}

int main(void)
{
    int numbers[] = {10, 15, 20, 30, 45, 60, 7, 14, 21};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;
    int *result = NULL;
    size_t result_count = 0;
    size_t i;
    int status;

    status = find_divisible(numbers, count, m, n, &result, &result_count);
    if (status != 0) {
        fprintf(stderr, "Error: Invalid input or memory allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Numbers divisible by %d and %d: ", m, n);
    for (i = 0; i < result_count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}