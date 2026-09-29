#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool is_concatenation_of_another_string(const char *str)
{
    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);

    if (length < 2U) {
        return false;
    }

    for (size_t pattern_length = 1U; pattern_length <= length / 2U; ++pattern_length) {
        if (length % pattern_length != 0U) {
            continue;
        }

        bool matches = true;

        for (size_t i = pattern_length; i < length; ++i) {
            if (str[i] != str[i % pattern_length]) {
                matches = false;
                break;
            }
        }

        if (matches) {
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
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (length == sizeof input - 1U && !feof(stdin)) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    puts(is_concatenation_of_another_string(input) ? "true" : "false");
    return 0;
}