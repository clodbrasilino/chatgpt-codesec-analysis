#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT64_DECIMAL_DIGITS 20U
#define UINT64_DECIMAL_BUFFER_SIZE (UINT64_DECIMAL_DIGITS + 1U)
#define INPUT_BUFFER_SIZE 128U

static int next_bigger(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_BUFFER_SIZE];
    size_t length;
    size_t pivot;
    size_t successor;
    uint64_t value = 0;
    int written;

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

    for (size_t left = pivot + 1U, right = length - 1U; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    for (size_t i = 0; i < length; ++i) {
        uint64_t digit;

        if (digits[i] < '0' || digits[i] > '9') {
            return 0;
        }

        digit = (uint64_t)(digits[i] - '0');
        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return 0;
        }

        value = value * UINT64_C(10) + digit;
    }

    *result = value;
    return 1;
}

static int discard_line(void)
{
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }

    return character == '\n' || feof(stdin);
}

static int read_uint64(uint64_t *result)
{
    char input[INPUT_BUFFER_SIZE];
    char *cursor;
    char *end;
    uintmax_t value;

    if (result == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        discard_line();
        return 0;
    }

    cursor = input;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (!isdigit((unsigned char)*cursor)) {
        return 0;
    }

    errno = 0;
    value = strtoumax(cursor, &end, 10);
    if (errno == ERANGE || end == cursor || value > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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