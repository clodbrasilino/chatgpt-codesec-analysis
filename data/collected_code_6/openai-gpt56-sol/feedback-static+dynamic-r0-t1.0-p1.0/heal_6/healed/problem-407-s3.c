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
    int length;
    int pivot;
    int successor;
    uint64_t value = 0;

    if (result == NULL) {
        return false;
    }

    length = snprintf(digits, sizeof digits, "%" PRIu64, number);
    if (length < 2 || (size_t)length >= sizeof digits) {
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

    for (int left = pivot + 1, right = length - 1; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    for (int index = 0; index < length; ++index) {
        uint64_t digit = (uint64_t)(digits[index] - '0');

        if (digit > 9U || value > (UINT64_MAX - digit) / UINT64_C(10)) {
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
    char *cursor;
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return false;
    }

    for (cursor = input; *cursor != '\0' && *cursor != '\n'; ++cursor) {
    }

    if (*cursor != '\n') {
        int character;

        if (!feof(stdin)) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);
        }

        return false;
    }

    *cursor = '\0';
    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE || parsed > UINT64_MAX) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
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

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}