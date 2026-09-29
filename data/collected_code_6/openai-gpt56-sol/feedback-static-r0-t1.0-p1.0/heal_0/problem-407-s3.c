#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool next_bigger_number(uint64_t number, uint64_t *result)
{
    char digits[21];
    int length;
    int pivot;
    int successor;

    if (result == NULL) {
        return false;
    }

    length = snprintf(digits, sizeof(digits), "%" PRIu64, number);
    if (length < 0 || (size_t)length >= sizeof(digits)) {
        return false;
    }

    pivot = length - 2;
    while (pivot >= 0 && digits[pivot] >= digits[pivot + 1]) {
        --pivot;
    }

    if (pivot < 0) {
        return false;
    }

    successor = length - 1;
    while (digits[successor] <= digits[pivot]) {
        --successor;
    }

    {
        char temporary = digits[pivot];
        digits[pivot] = digits[successor];
        digits[successor] = temporary;
    }

    for (int left = pivot + 1, right = length - 1; left < right; ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    {
        uint64_t value = 0;

        for (int index = 0; index < length; ++index) {
            uint64_t digit;

            if (digits[index] < '0' || digits[index] > '9') {
                return false;
            }

            digit = (uint64_t)(digits[index] - '0');
            if (value > (UINT64_MAX - digit) / 10U) {
                return false;
            }

            value = value * 10U + digit;
        }

        *result = value;
    }

    return true;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!next_bigger_number(number, &result)) {
        puts("-1");
        return 0;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}