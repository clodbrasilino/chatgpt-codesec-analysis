#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool value_exists(const int *sequence, size_t length, int value)
{
    if (sequence == NULL || length == 0) {
        return false;
    }

    for (size_t i = 0; i < length; i++) {
        if (sequence[i] == value) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    int numbers[] = {4, 8, 15, 16, 23, 42};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int target = 15;

    if (value_exists(numbers, count, target)) {
        if (printf("Value %d exists in the sequence.\n", target) < 0) {
            return 1;
        }
    } else {
        if (printf("Value %d does not exist in the sequence.\n", target) < 0) {
            return 1;
        }
    }

    target = 99;

    if (value_exists(numbers, count, target)) {
        if (printf("Value %d exists in the sequence.\n", target) < 0) {
            return 1;
        }
    } else {
        if (printf("Value %d does not exist in the sequence.\n", target) < 0) {
            return 1;
        }
    }

    return 0;
}