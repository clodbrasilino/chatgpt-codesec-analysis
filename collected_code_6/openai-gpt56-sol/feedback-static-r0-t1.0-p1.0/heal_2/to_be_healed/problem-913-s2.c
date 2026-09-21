#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool ends_with_number(const char *str, size_t length)
{
    if (str == NULL || length == 0) {
        return false;
    }

    return isdigit((unsigned char)str[length - 1]) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length < sizeof input - 1) {
            input[length++] = (char)ch;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    input[length] = '\0';

    printf("%s\n", ends_with_number(input, length) ? "true" : "false");
    return 0;
}