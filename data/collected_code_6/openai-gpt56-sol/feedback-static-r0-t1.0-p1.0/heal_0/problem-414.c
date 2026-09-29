#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool contains_value(const int *sequence, size_t length, int value)
{
    if (sequence == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (sequence[i] == value) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int sequence[] = {4, 8, 15, 16, 23, 42};
    const size_t length = sizeof(sequence) / sizeof(sequence[0]);
    int value = 0;

    if (printf("Enter a value: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d", &value) != 1) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (contains_value(sequence, length, value)) {
        if (puts("Value exists in the sequence.") == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("Value does not exist in the sequence.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}