#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int print_numbers_with_positions(const char *str)
{
    size_t i;
    size_t len;
    size_t start;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }
            if (printf("Number: %.*s, Position: %zu\n",
                       (int)(i - start), &str[start], start) < 0) {
                return -1;
            }
        } else {
            i++;
        }
    }

    return 0;
}

int main(void)
{
    const char *input = "abc123def45gh6";

    if (print_numbers_with_positions(input) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}