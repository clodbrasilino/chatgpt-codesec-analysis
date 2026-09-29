#include <stdio.h>
#include <stddef.h>

size_t count_in_range(const int *arr, size_t size, int lower, int upper)
{
    size_t count = 0;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;

    if (arr == NULL) {
        fprintf(stderr, "Error: NULL array pointer\n");
        return 0;
    }

    if (size == 0) {
        return 0;
    }

    if (lower > upper) {
        temp = lower;
        lower = upper;
        upper = temp;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] >= lower && arr[i] <= upper) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {5, 12, 3, 8, 21, 7, 15, 1, 10, 18};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int lower = 5;
    int upper = 15;
    size_t result;

    result = count_in_range(numbers, size, lower, upper);

    printf("Number of elements within range [%d, %d]: %zu\n", lower, upper, result);

    result = count_in_range(NULL, size, lower, upper);
    printf("Null pointer test result: %zu\n", result);

    result = count_in_range(numbers, 0, lower, upper);
    printf("Empty array test result: %zu\n", result);

    return 0;
}