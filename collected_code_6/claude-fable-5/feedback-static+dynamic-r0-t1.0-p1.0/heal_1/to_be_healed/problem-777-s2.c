#include <stdio.h>
#include <stdlib.h>

long long sum_non_repeated(const int *arr, size_t n)
{
    long long sum = 0;
    size_t i;
    size_t j;
    /* Possible weaknesses found:
     *  The scope of the variable 'repeated' can be reduced. [variableScope]
     */
    int repeated;

    if (arr == NULL || n == 0U) {
        return 0;
    }

    for (i = 0U; i < n; i++) {
        repeated = 0;
        for (j = 0U; j < n; j++) {
            if ((i != j) && (arr[i] == arr[j])) {
                repeated = 1;
                break;
            }
        }
        if (repeated == 0) {
            sum += (long long)arr[i];
        }
    }

    return sum;
}

int main(void)
{
    int numbers[] = {3, 7, 3, 2, 8, 7, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    result = sum_non_repeated(numbers, count);

    if (printf("Sum of non-repeated elements: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}