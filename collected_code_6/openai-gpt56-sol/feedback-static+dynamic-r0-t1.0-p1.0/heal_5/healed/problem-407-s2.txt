#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_BUFFER_SIZE (sizeof("18446744073709551615"))

static int next_bigger(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_BUFFER_SIZE];
    size_t length = 0;
    size_t pivot;
    size_t successor;
    uint64_t value = 0;

    if (result == NULL) {
        return 0;
    }

    do {
        digits[length++] = (char)('0' + number % 10U);
        number /= 10U;
    } while (number != 0U && length < sizeof digits);

    if (number != 0U || length < 2U) {
        return 0;
    }

    for (size_t left = 0, right = length - 1U; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    pivot = length - 2U;
    for (;;) {
        if (digits[pivot] < digits[pivot + 1U]) {
            break;
        }

        if (pivot == 0U) {
            return 0;
        }

        --pivot;
    }

    successor = length - 1U;
    while (digits[successor] <= digits[pivot]) {
        --successor;
    }

    {
        char temporary = digits[pivot];
        digits[pivot] = digits[successor];
        digits[successor] = temporary;
    }

    for (size_t left = pivot + 1U, right = length - 1U; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    for (size_t i = 0; i < length; ++i) {
        uint64_t digit = (uint64_t)(digits[i] - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        value = value * UINT64_C(10) + digit;
    }

    *result = value;
    return 1;
}

static int read_uint64(uint64_t *result)
{
    uint64_t value = 0;
    int character;
    int saw_digit = 0;
    int trailing_space = 0;
    int valid = 1;

    if (result == NULL) {
        return 0;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        unsigned char current = (unsigned char)character;

        if (!saw_digit) {
            if (isspace(current)) {
                continue;
            }

            if (!isdigit(current)) {
                valid = 0;
                continue;
            }
        } else if (trailing_space) {
            if (isspace(current)) {
                continue;
            }

            valid = 0;
            continue;
        } else if (isspace(current)) {
            trailing_space = 1;
            continue;
        } else if (!isdigit(current)) {
            valid = 0;
            continue;
        }

        if (valid && isdigit(current)) {
            uint64_t digit = (uint64_t)(current - (unsigned char)'0');

            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                valid = 0;
                continue;
            }

            value = value * UINT64_C(10) + digit;
            saw_digit = 1;
        }
    }

    if (!valid || !saw_digit) {
        return 0;
    }

    *result = value;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (!read_uint64(&number)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_bigger(number, &result)) {
        puts("No bigger number can be formed");
        return EXIT_SUCCESS;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}