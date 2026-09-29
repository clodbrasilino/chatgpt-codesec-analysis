#include <stdio.h>
#include <string.h>

static int is_binary_string(const char *str)
{
    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (*str != '0' && *str != '1') {
            return 0;
        }
        ++str;
    }

    return 1;
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

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
        if (length > 0 && input[length - 1] == '\r') {
            input[length - 1] = '\0';
        }
    } else if (length == sizeof input - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character != '\n' && character != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            return 1;
        }
    }

    puts(is_binary_string(input) ? "Binary string" : "Not a binary string");
    return 0;
}