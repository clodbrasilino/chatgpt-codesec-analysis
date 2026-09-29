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

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No input provided.\n", stderr);
        }
        return 1;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        input[length - 1U] = '\0';
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}