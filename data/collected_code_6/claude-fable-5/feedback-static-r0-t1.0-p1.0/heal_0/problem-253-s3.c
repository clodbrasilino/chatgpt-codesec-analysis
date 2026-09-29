#include <stdio.h>
#include <stdlib.h>

size_t count_occurrences(const int *list, size_t length, int target)
{
    size_t count = 0;
    size_t i;

    if (list == NULL) {
        return 0;
    }

    for (i = 0; i < length; i++) {
        if (list[i] == target) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int numbers[] = {3, 7, 3, 9, 3, 1, 7, 3};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int target = 3;
    size_t result;

    result = count_occurrences(numbers, length, target);

    if (printf("The value %d appears %zu times in the list.\n", target, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}