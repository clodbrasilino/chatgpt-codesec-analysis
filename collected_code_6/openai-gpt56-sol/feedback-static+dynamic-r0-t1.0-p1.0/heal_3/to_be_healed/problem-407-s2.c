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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[UINT64_DECIMAL_BUFFER_SIZE];
    size_t length;
    size_t pivot;
    size_t successor;
    size_t left;
    size_t right;
    char temporary;
    char *end;
    uintmax_t value;
    int written;

    if (result == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
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

    temporary = digits[pivot];
    digits[pivot] = digits[successor];
    digits[successor] = temporary;

    left = pivot + 1U;
    right = length - 1U;

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

    if (errno == ERANGE || end == digits || *end != '\0' ||
        value > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE];
    char *start;
    char *end;
    uintmax_t value;
    uint64_t result;
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] != '\0') {
        size_t length = 0U;

        while (input[length] != '\0') {
            ++length;
        }

        if (length > 0U && input[length - 1U] != '\n' && !feof(stdin)) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value > (uintmax_t)UINT64_MAX) {
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

    if (!next_bigger((uint64_t)value, &result)) {
        puts("No bigger number can be formed");
        return EXIT_SUCCESS;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}