#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 64

typedef enum {
    HEX_EVEN = 0,
    HEX_ODD = 1,
    HEX_INVALID = -1
} hex_parity_t;

static hex_parity_t check_hex_parity(const char *hex_str)
{
    size_t len;
    size_t i;
    size_t start = 0;
    char last;

    if (hex_str == NULL) {
        return HEX_INVALID;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(hex_str);
    if (len == 0U) {
        return HEX_INVALID;
    }

    if (len > 2U && hex_str[0] == '0' &&
        (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        start = 2U;
    }

    if (start >= len) {
        return HEX_INVALID;
    }

    for (i = start; i < len; i++) {
        if (isxdigit((unsigned char)hex_str[i]) == 0) {
            return HEX_INVALID;
        }
    }

    last = hex_str[len - 1U];

    if (last >= '0' && last <= '9') {
        return (((last - '0') % 2) == 0) ? HEX_EVEN : HEX_ODD;
    }

    last = (char)tolower((unsigned char)last);
    return (((last - 'a' + 10) % 2) == 0) ? HEX_EVEN : HEX_ODD;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    char *newline;
    hex_parity_t result;

    printf("Enter a hexadecimal number: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    }

    result = check_hex_parity(input);

    if (result == HEX_INVALID) {
        fprintf(stderr, "Invalid hexadecimal input.\n");
        return EXIT_FAILURE;
    }

    if (result == HEX_EVEN) {
        printf("The hexadecimal number %s is even.\n", input);
    } else {
        printf("The hexadecimal number %s is odd.\n", input);
    }

    return EXIT_SUCCESS;
}