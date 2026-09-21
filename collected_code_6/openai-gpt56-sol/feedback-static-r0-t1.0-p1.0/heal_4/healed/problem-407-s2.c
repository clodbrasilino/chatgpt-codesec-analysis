#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UINT64_DECIMAL_DIGITS 20U
#define INPUT_SIZE 128U

static int next_bigger(uint64_t number, uint64_t *result)
{
    char digits[UINT64_DECIMAL_DIGITS + 1U];
    int length;
    size_t pivot;
    size_t successor;
    size_t left;
    size_t right;
    char temporary;
    char *end;
    uintmax_t value;

    if (result == NULL) {
        return 0;
    }

    length = snprintf(digits, sizeof digits, "%" PRIu64, number);
    if (length <= 0 || (size_t)length >= sizeof digits) {
        return 0;
    }

    pivot = (size_t)length - 1U;
    while (pivot > 0U && digits[pivot - 1U] >= digits[pivot]) {
        --pivot;
    }

    if (pivot == 0U) {
        return 0;
    }

    --pivot;
    successor = (size_t)length - 1U;

    while (digits[successor] <= digits[pivot]) {
        --successor;
    }

    temporary = digits[pivot];
    digits[pivot] = digits[successor];
    digits[successor] = temporary;

    left = pivot + 1U;
    right = (size_t)length - 1U;

    while (left < right) {
        temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
        ++left;
        --right;
    }

    errno = 0;
    value = strtoumax(digits, &end, 10);

    if (errno == ERANGE || end == digits || *end != '\0' ||
        value > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    char input[INPUT_SIZE];
    char *end;
    uintmax_t value;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t length = 0U;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        if (length > 0U && input[length - 1U] != '\n') {
            int character = getchar();

            if (character != EOF) {
                while (character != '\n' && character != EOF) {
                    character = getchar();
                }

                fputs("Invalid input\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!next_bigger((uint64_t)value, &result)) {
        puts("No bigger number can be formed");
        return EXIT_SUCCESS;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}