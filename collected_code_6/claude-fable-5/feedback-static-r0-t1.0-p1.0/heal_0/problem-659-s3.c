#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static int print_duplicates(const int *arr, size_t len)
{
    size_t i;
    size_t j;
    int found;

    if (arr == NULL) {
        return -1;
    }

    found = 0;

    for (i = 0U; i < len; i++) {
        int seen_before = 0;

        for (j = 0U; j < i; j++) {
            if (arr[j] == arr[i]) {
                seen_before = 1;
                break;
            }
        }

        if (seen_before == 0) {
            for (j = i + 1U; j < len; j++) {
                if (arr[j] == arr[i]) {
                    if (printf("%d\n", arr[i]) < 0) {
                        return -1;
                    }
                    found = 1;
                    break;
                }
            }
        }
    }

    if (found == 0) {
        if (printf("No duplicates found\n") < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const int numbers[] = { 4, 7, 2, 4, 9, 7, 1, 2, 4 };
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (print_duplicates(numbers, count) != 0) {
        (void)fprintf(stderr, "Error while printing duplicates\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}