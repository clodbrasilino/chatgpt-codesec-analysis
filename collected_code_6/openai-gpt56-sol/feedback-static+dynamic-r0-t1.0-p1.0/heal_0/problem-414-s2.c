#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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
    const int sequence[] = {3, 7, 11, 15, 19};
    const size_t length = sizeof(sequence) / sizeof(sequence[0]);
    int value = 0;

    if (printf("Enter an integer: ") < 0) {
        return 1;
    }

    if (scanf("%d", &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (contains_value(sequence, length, value)) {
        if (puts("Value exists in the sequence.") == EOF) {
            return 1;
        }
    } else {
        if (puts("Value does not exist in the sequence.") == EOF) {
            return 1;
        }
    }

    return 0;
}