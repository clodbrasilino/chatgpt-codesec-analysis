#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int next_bigger(uint64_t number, uint64_t *result)
{
    char digits[32];
    int length;
    int pivot;
    int successor;
    int left;
    int right;
    char temporary;
    char *end;
    uintmax_t value;

    if (result == NULL) {
        return 0;
    }

    length = snprintf(digits, sizeof(digits), "%" PRIu64, number);
    if (length < 0 || (size_t)length >= sizeof(digits)) {
        return 0;
    }

    pivot = length - 2;
    while (pivot >= 0 && digits[pivot] >= digits[pivot + 1]) {
        --pivot;
    }

    if (pivot < 0) {
        return 0;
    }

    successor = length - 1;
    while (digits[successor] <= digits[pivot]) {
        --successor;
    }

    temporary = digits[pivot];
    digits[pivot] = digits[successor];
    digits[successor] = temporary;

    left = pivot + 1;
    right = length - 1;
    while (left < right) {
        temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
        ++left;
        --right;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(digits, &end, 10);

    if (errno == ERANGE || end == digits || *end != '\0' || value > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    if (scanf("%" SCNu64, &number) != 1) {
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