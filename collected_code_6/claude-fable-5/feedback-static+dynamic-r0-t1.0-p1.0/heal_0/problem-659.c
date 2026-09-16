#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_duplicates(const int *arr, size_t len)
{
    if (arr == NULL || len < 2U) {
        return;
    }

    for (size_t i = 0U; i < len; i++) {
        bool already_reported = false;

        for (size_t j = 0U; j < i; j++) {
            if (arr[j] == arr[i]) {
                already_reported = true;
                break;
            }
        }

        if (already_reported) {
            continue;
        }

        for (size_t j = i + 1U; j < len; j++) {
            if (arr[j] == arr[i]) {
                if (printf("%d\n", arr[i]) < 0) {
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }
    }
}

int main(void)
{
    const int numbers[] = {4, 2, 7, 2, 9, 4, 1, 7, 4};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_duplicates(numbers, count);

    return EXIT_SUCCESS;
}