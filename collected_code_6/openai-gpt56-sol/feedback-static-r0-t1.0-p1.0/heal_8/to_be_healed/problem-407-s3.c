#include <ctype.h>
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[UINT64_DECIMAL_BUFFER_SIZE];
    size_t length = 0U;

    if (result == NULL) {
        return false;
    }

    do {
        if (length >= sizeof digits - 1U) {
            return false;
        }

        digits[length++] = (char)('0' + number % UINT64_C(10));
        number /= UINT64_C(10);
    } while (number != UINT64_C(0));

    for (size_t left = 0U, right = length - 1U; left < right;
         ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    digits[length] = '\0';

    size_t pivot = length - 1U;

    while (pivot > 0U && digits[pivot - 1U] >= digits[pivot]) {
        --pivot;
    }

    if (pivot == 0U) {
        return false;
    }

    --pivot;

    size_t successor = length - 1U;

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

    uint64_t value = UINT64_C(0);

    for (size_t index = 0U; index < length; ++index) {
        uint64_t digit = (uint64_t)(digits[index] - '0');

        if (value > (UINT64_MAX - digit) / UINT64_C(10)) {
            return false;
        }

        value = value * UINT64_C(10) + digit;
    }

    *result = value;
    return true;
}

static bool read_input(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2U) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    size_t length = 0U;

    while (length < capacity && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length < capacity && buffer[length] == '\n') {
        buffer[length] = '\0';
        return length != 0U;
    }

    if (feof(stdin)) {
        return length != 0U;
    }

    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    buffer[0] = '\0';
    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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