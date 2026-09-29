#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_DIGITS 20U
#define UINT64_DECIMAL_BUFFER_SIZE (UINT64_DECIMAL_DIGITS + 1U)
#define INPUT_BUFFER_SIZE 128U

static bool next_bigger_number(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_BUFFER_SIZE];
    size_t length = 0U;
    size_t pivot;
    size_t successor;

    if (result == NULL) {
        return false;
    }

    do {
        if (length >= UINT64_DECIMAL_DIGITS) {
            return false;
        }

        digits[length++] = (char)('0' + (number % UINT64_C(10)));
        number /= UINT64_C(10);
    } while (number != UINT64_C(0));

    for (size_t left = 0U, right = length - 1U; left < right; ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    digits[length] = '\0';

    pivot = length - 1U;
    while (pivot > 0U && digits[pivot - 1U] >= digits[pivot]) {
        --pivot;
    }

    if (pivot == 0U) {
        return false;
    }

    --pivot;
    successor = length - 1U;

    while (successor > pivot && digits[successor] <= digits[pivot]) {
        --successor;
    }

    if (successor == pivot) {
        return false;
    }

    {
        char temporary = digits[pivot];
        digits[pivot] = digits[successor];
        digits[successor] = temporary;
    }

    for (size_t left = pivot + 1U, right = length - 1U;
         left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    {
        uint64_t value = UINT64_C(0);

        for (size_t index = 0U; index < length; ++index) {
            uint64_t digit;

            if (digits[index] < '0' || digits[index] > '9') {
                return false;
            }

            digit = (uint64_t)(digits[index] - '0');

            if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
                return false;
            }

            value = value * UINT64_C(10) + digit;
        }

        *result = value;
    }

    return true;
}

static bool read_input(char *buffer, size_t capacity)
{
    size_t length = 0U;
    int character;

    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= capacity - 1U) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            buffer[0] = '\0';
            return false;
        }

        buffer[length++] = (char)character;
    }

    buffer[length] = '\0';

    if (character == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return false;
    }

    return length != 0U;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (!read_input(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\v' ||
           *end == '\f' || *end == '\r') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_bigger_number((uint64_t)parsed, &result)) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}