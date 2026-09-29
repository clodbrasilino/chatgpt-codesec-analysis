#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_BUFFER_SIZE 21U
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

static void discard_line(void)
{
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
    }
}

static int read_uint64(uint64_t *result)
{
    char input[INPUT_BUFFER_SIZE];
    char *cursor;
    char *end;
    uintmax_t value;
    size_t length;

    if (result == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    for (length = 0U; length < sizeof input && input[length] != '\0'; ++length) {
    }

    if (length == sizeof input) {
        discard_line();
        return 0;
    }

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
    } else if (!feof(stdin)) {
        discard_line();
        return 0;
    }

    cursor = input;
    while (*cursor != '\0' && isspace((unsigned char)*cursor) != 0) {
        ++cursor;
    }

    if (isdigit((unsigned char)*cursor) == 0) {
        return 0;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor || value > UINT64_MAX) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end) != 0) {
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