#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 4096 };

static bool is_concatenation_of_another_string(const char *str, size_t length)
{
    if (str == NULL || length < 2U) {
        return false;
    }

    for (size_t pattern_length = 1U;
         pattern_length <= length / 2U;
         ++pattern_length) {
        if (length % pattern_length != 0U) {
            continue;
        }

        size_t i = pattern_length;

        while (i < length && str[i] == str[i % pattern_length]) {
            ++i;
        }

        if (i == length) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];
    size_t length = 0U;
    bool too_long = false;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1U < sizeof input) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (character == EOF && length == 0U && !too_long) {
        return 1;
    }

    if (too_long) {
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    input[length] = '\0';

    puts(is_concatenation_of_another_string(input, length)
             ? "true"
             : "false");

    return 0;
}