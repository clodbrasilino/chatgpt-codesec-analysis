#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool has_two_alternating_characters(const char *str)
{
    size_t length;
    char first;
    char second;

    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(str);
    if (length < 2U) {
        return false;
    }

    first = str[0];
    second = str[1];

    if (first == second) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        const char expected = (i % 2U == 0U) ? first : second;

        if (str[i] != expected) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            return 1;
        }
    }

    puts(has_two_alternating_characters(input) ? "Yes" : "No");
    return 0;
}