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
    size_t pivot;
    size_t successor;
    uint64_t value = UINT64_C(0);

    if (result == NULL) {
        return false;
    }

    length = snprintf(digits, sizeof digits, "%" PRIu64, number);
    if (length < 2 || (size_t)length >= sizeof digits) {
        return false;
    }

    pivot = (size_t)length - 1U;
    while (pivot > 0U && digits[pivot - 1U] >= digits[pivot]) {
        --pivot;
    }

    if (pivot == 0U) {
        return false;
    }

    --pivot;
    successor = (size_t)length - 1U;

    while (digits[successor] <= digits[pivot]) {
        --successor;
    }

    {
        char temporary = digits[pivot];
        digits[pivot] = digits[successor];
        digits[successor] = temporary;
    }

    for (size_t left = pivot + 1U, right = (size_t)length - 1U;
         left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    for (size_t index = 0U; index < (size_t)length; ++index) {
        uint64_t digit = (uint64_t)(digits[index] - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        value = value * UINT64_C(10) + digit;
    }

    *result = value;
    return true;
}

static void discard_line(void)
{
    int character;

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);
}

static bool read_uint64(uint64_t *value)
{
    char input[INPUT_SIZE];
    char *newline;
    char *cursor;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return false;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return false;
    }

    newline = NULL;
    for (size_t index = 0U; index < sizeof input; ++index) {
        if (input[index] == '\n') {
            newline = &input[index];
            break;
        }

        if (input[index] == '\0') {
            break;
        }
    }

    if (newline == NULL) {
        if (!feof(stdin)) {
            discard_line();
        }
        return false;
    }

    *newline = '\0';
    cursor = input;

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\v' || *cursor == '\f' ||
           *cursor == '\r') {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '+' || *cursor == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return false;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\v' || *end == '\f' ||
           *end == '\r') {
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
        if (fputs("Invalid input\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (!next_bigger_number(number, &result)) {
        if (puts("-1") == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}