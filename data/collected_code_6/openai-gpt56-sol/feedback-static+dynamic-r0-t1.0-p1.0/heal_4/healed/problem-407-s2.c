#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_BUFFER_SIZE (sizeof("18446744073709551615"))

static int next_bigger(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_BUFFER_SIZE];
    size_t length;
    size_t pivot;
    size_t successor;
    int written;
    char *end;
    uintmax_t value;

    if (result == NULL) {
        return 0;
    }

    written = snprintf(digits, sizeof digits, "%" PRIu64, number);
    if (written < 0 || (size_t)written >= sizeof digits) {
        return 0;
    }

    length = (size_t)written;
    if (length < 2U) {
        return 0;
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
    while (successor > pivot && digits[successor] <= digits[pivot]) {
        --successor;
    }

    if (successor == pivot) {
        return 0;
    }

    {
        char temporary = digits[pivot];
        digits[pivot] = digits[successor];
        digits[successor] = temporary;
    }

    {
        size_t left = pivot + 1U;
        size_t right = length - 1U;

        while (left < right) {
            char temporary = digits[left];
            digits[left] = digits[right];
            digits[right] = temporary;
            ++left;
            --right;
        }
    }

    errno = 0;
    end = NULL;
    value = strtoumax(digits, &end, 10);

    if (errno == ERANGE || end == NULL || end == digits || *end != '\0' ||
        value > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

static int read_uint64(uint64_t *result)
{
    uintmax_t value;
    int character;
    int first_nonspace;
    int saw_digit;

    if (result == NULL) {
        return 0;
    }

    value = 0;
    first_nonspace = 1;
    saw_digit = 0;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        unsigned char current = (unsigned char)character;

        if (first_nonspace && isspace(current)) {
            continue;
        }

        first_nonspace = 0;

        if (isdigit(current)) {
            unsigned int digit = (unsigned int)(current - (unsigned char)'0');

            if (value > (UINT64_MAX - digit) / 10U) {
                do {
                    character = fgetc(stdin);
                } while (character != '\n' && character != EOF);
                return 0;
            }

            value = value * 10U + digit;
            saw_digit = 1;
            continue;
        }

        if (saw_digit && isspace(current)) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF &&
                     isspace((unsigned char)character));

            if (character == '\n' || character == EOF) {
                *result = (uint64_t)value;
                return 1;
            }
        }

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        return 0;
    }

    if (!saw_digit) {
        return 0;
    }

    *result = (uint64_t)value;
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