#include <stdbool.h>
#include <stdio.h>

enum { INPUT_CAPACITY = 1024 };

static bool is_binary_string(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string;
         *p != '\0';
         ++p) {
        if (*p != (unsigned char)'0' && *p != (unsigned char)'1') {
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
    char input[INPUT_CAPACITY];
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= sizeof input) {
            while (character != '\n' && character != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = getchar();
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return 1;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (character == EOF && length == 0U) {
        fputs("No input provided.\n", stderr);
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}