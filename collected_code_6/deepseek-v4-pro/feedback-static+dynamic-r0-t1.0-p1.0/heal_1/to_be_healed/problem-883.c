#include <stdio.h>
#include <stdlib.h>

int* find_divisible_by_m_and_n(const int *numbers, size_t count, int m, int n, size_t *result_count) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_count==NULL' is not redundant
     */
    if (numbers == NULL || result_count == NULL || count == 0 || m == 0 || n == 0) {
        /* Possible weaknesses found:
         *  Either the condition 'result_count==NULL' is redundant or there is possible null pointer dereference: result_count. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *result_count = 0;
        return NULL;
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    size_t result_index = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            result[result_index++] = numbers[i];
        }
    }

    *result_count = result_index;
    if (result_index == 0) {
        free(result);
        return NULL;
    }

    int *trimmed = realloc(result, result_index * sizeof(int));
    if (trimmed == NULL) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    return trimmed;
}

int main(void) {
    int numbers[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t result_count = 0;

    int *divisible = find_divisible_by_m_and_n(numbers, count, 3, 5, &result_count);

    if (divisible != NULL && result_count > 0) {
        printf("Numbers divisible by 3 and 5: ");
        for (size_t i = 0; i < result_count; i++) {
            printf("%d", divisible[i]);
            if (i < result_count - 1) {
                printf(", ");
            }
        }
        printf("\n");
        free(divisible);
    } else {
        printf("No numbers divisible by 3 and 5 found.\n");
    }

    return 0;
}