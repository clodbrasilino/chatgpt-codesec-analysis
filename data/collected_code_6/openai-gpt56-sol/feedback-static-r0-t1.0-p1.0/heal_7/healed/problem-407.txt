#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_DIGITS 20U
#define INPUT_SIZE 128U

static bool next_bigger_number(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_DIGITS + 1U];
    size_t length = 0U;
    size_t pivot;
    size_t successor;
    uint64_t value = 0U;

    if (result == NULL) {
        return false;
    }

    do {
        if (length >= UINT64_DECIMAL_DIGITS) {
            return false;
        }

        digits[length++] = (char)('0' + (number % UINT64_C(10)));
        number /= UINT64_C(10);
    } while (number != 0U);

    for (size_t left = 0U, right = length - 1U; left < right;
         ++left, --right) {
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

    for (size_t left = pivot + 1U, right = length - 1U; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    for (size_t i = 0U; i < length; ++i) {
        uint64_t digit;

        if (digits[i] < '0' || digits[i] > '9') {
            return false;
        }

        digit = (uint64_t)(digits[i] - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        value = value * UINT64_C(10) + digit;
    }

    *result = value;
    return true;
}

static bool read_uint64(uint64_t *value)
{
    char input[INPUT_SIZE];
    char *begin;
    char *end;
    uintmax_t parsed;
    size_t length = 0U;

    if (value == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return false;
    }

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return false;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        return false;
    }

    begin = input;

    while (*begin != '\0' && isspace((unsigned char)*begin) != 0) {
        ++begin;
    }

    if (*begin == '\0' || *begin == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(begin, &end, 10);

    if (errno == ERANGE || end == begin || parsed > UINT64_MAX) {
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *value = (uint64_t)parsed;
    return true;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (!read_uint64(&number)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_bigger_number(number, &result)) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}