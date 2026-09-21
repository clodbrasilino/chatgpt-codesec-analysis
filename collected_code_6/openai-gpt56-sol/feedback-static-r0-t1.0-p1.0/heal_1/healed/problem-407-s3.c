#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool next_bigger_number(uint64_t number, uint64_t *result)
{
    char digits[UINT64_C(18446744073709551615) > 0 ? 21 : 21];
    int length;
    int pivot;
    int successor;

    if (result == NULL) {
        return false;
    }

    length = snprintf(digits, sizeof digits, "%" PRIu64, number);
    if (length < 0 || (size_t)length >= sizeof digits) {
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
    while (successor > pivot && digits[successor] <= digits[pivot]) {
        --successor;
    }

    {
        char temporary = digits[pivot];
        digits[pivot] = digits[successor];
        digits[successor] = temporary;
    }

    for (int left = pivot + 1, right = length - 1; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    {
        uint64_t value = 0;

        for (int index = 0; index < length; ++index) {
            uint64_t digit = (uint64_t)(digits[index] - '0');

            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                return false;
            }

            value = value * UINT64_C(10) + digit;
        }

        *result = value;
    }

    return true;
}

int main(void)
{
    char input[128];
    char *end;
    unsigned long long parsed;
    uint64_t number;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0' || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    number = (uint64_t)parsed;

    if (!next_bigger_number(number, &result)) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}