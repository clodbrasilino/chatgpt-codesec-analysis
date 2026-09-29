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
    char digits[UINT64_DECIMAL_DIGITS];
    size_t length = 0;

    if (result == NULL) {
        return false;
    }

    do {
        if (length == sizeof digits) {
            return false;
        }

        digits[length++] = (char)('0' + number % UINT64_C(10));
        number /= UINT64_C(10);
    } while (number != 0);

    for (size_t left = 0, right = length - 1; left < right; ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    size_t pivot = length - 1;

    while (pivot > 0 && digits[pivot - 1] >= digits[pivot]) {
        --pivot;
    }

    if (pivot == 0) {
        return false;
    }

    --pivot;

    size_t successor = length - 1;

    while (successor > pivot && digits[successor] <= digits[pivot]) {
        --successor;
    }

    if (successor == pivot) {
        return false;
    }

    char temporary = digits[pivot];
    digits[pivot] = digits[successor];
    digits[successor] = temporary;

    for (size_t left = pivot + 1, right = length - 1; left < right; ++left, --right) {
        temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    uint64_t value = 0;

    for (size_t i = 0; i < length; ++i) {
        const uint64_t digit = (uint64_t)(digits[i] - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        value = value * UINT64_C(10) + digit;
    }

    *result = value;
    return true;
}

int main(void)
{
    char input[INPUT_SIZE];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
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