#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

long long *add_consecutive(const int *list, size_t size, size_t *result_size)
{
    long long *result;
    size_t i;

    if (list == NULL || result_size == NULL || size < 2) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    result = malloc((size - 1) * sizeof(*result));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (i = 0; i < size - 1; i++) {
        result[i] = (long long)list[i] + list[i + 1];
    }

    *result_size = size - 1;
    return result;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t result_size = 0;
    size_t i;
    long long *result = add_consecutive(list, size, &result_size);

    if (result == NULL) {
        fprintf(stderr, "Error: failed to compute consecutive sums\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0; i < result_size; i++) {
        printf("%lld", result[i]);
        if (i < result_size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(result);
    return EXIT_SUCCESS;
}