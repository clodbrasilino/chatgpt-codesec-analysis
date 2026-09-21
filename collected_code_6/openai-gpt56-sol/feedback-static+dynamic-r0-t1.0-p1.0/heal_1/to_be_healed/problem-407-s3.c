#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool next_bigger_number(uint64_t number, uint64_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char digits[21];
    int length;
    int pivot;
    int successor;

    if (result == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder snprintf: If format strings can be influenced by an attacker, they can be exploited, and note that sprintf variations do not always \0-terminate (CWE-134). Use a constant for the format specification. (risk 4, format)
     */
    length = snprintf(digits, sizeof(digits), "%" PRIu64, number);
    if (length < 0 || (size_t)length >= sizeof(digits)) {
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

    for (int left = pivot + 1, right = length - 1; left < right; ++left, --right) {
        char temporary = digits[left];
        digits[left] = digits[right];
        digits[right] = temporary;
    }

    {
        uint64_t value = 0;

        for (int index = 0; index < length; ++index) {
            uint64_t digit;

            if (digits[index] < '0' || digits[index] > '9') {
                return false;
            }

            digit = (uint64_t)(digits[index] - '0');
            if (value > (UINT64_MAX - digit) / 10U) {
                return false;
            }

            value = value * 10U + digit;
        }

        *result = value;
    }

    return true;
}

int main(void)
{
    uint64_t number;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!next_bigger_number(number, &result)) {
        puts("-1");
        return 0;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}