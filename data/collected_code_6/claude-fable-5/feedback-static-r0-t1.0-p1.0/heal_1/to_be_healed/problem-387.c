#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_valid_hex(const char *str)
{
    size_t i = 0;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    if (len == 0) {
        return 0;
    }

    if (len > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        i = 2;
    }

    if (i >= len) {
        return 0;
    }

    for (; i < len; i++) {
        if (!isxdigit((unsigned char)str[i])) {
            return 0;
        }
    }

    return 1;
}

int is_hex_even(const char *hex, int *result)
{
    size_t len;
    char last;

    if (hex == NULL || result == NULL) {
        return -1;
    }

    if (!is_valid_hex(hex)) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(hex);
    last = hex[len - 1];

    if (last >= '0' && last <= '9') {
        *result = ((last - '0') % 2 == 0) ? 1 : 0;
    } else {
        last = (char)tolower((unsigned char)last);
        *result = ((last - 'a' + 10) % 2 == 0) ? 1 : 0;
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;
    int even = 0;

    printf("Enter a hexadecimal number: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (is_hex_even(buffer, &even) != 0) {
        fprintf(stderr, "Invalid hexadecimal input\n");
        return EXIT_FAILURE;
    }

    if (even) {
        printf("%s is even\n", buffer);
    } else {
        printf("%s is odd\n", buffer);
    }

    return EXIT_SUCCESS;
}