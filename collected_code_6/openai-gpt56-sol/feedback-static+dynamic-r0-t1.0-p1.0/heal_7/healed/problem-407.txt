#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_DIGITS 20U
#define INPUT_BUFFER_SIZE 128U

static bool next_bigger_number(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_DIGITS + 1U];
    int written;
    size_t length;
    size_t pivot;
    size_t successor;
    uint64_t value = UINT64_C(0);

    if (result == NULL) {
        return false;
    }

    written = snprintf(digits, sizeof digits, "%" PRIu64, number);
    if (written < 2 || (size_t)written >= sizeof digits) {
        return false;
    }

    length = (size_t)written;
    pivot = length - 2U;

    for (;;) {
        if (digits[pivot] < digits[pivot + 1U]) {
            break;
        }

        if (pivot == 0U) {
            return false;
        }

        --pivot;
    }

    successor = length - 1U;
    while (successor > pivot && digits[successor] <= digits[pivot]) {
        --successor;
    }

    if (successor <= pivot) {
        return false;
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

static bool read_input(char *buffer, size_t size)
{
    char *newline;
    int ch;

    if (buffer == NULL || size < 2U) {
        return false;
    }

    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }

    newline = NULL;
    for (char *p = buffer; *p != '\0'; ++p) {
        if (*p == '\n') {
            newline = p;
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
        return true;
    }

    if (feof(stdin)) {
        return true;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    if (ferror(stdin)) {
        return false;
    }

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    char *start;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (!read_input(input, sizeof input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start) != 0) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_bigger_number((uint64_t)parsed, &result)) {
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