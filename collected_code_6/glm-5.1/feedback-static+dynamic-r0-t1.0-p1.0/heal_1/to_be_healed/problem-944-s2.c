#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }

            size_t num_len = i - start;
            char *num_str = (char *)malloc(num_len + 1);
            if (num_str == NULL) {
                return;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, str + start, num_len);
            num_str[num_len] = '\0';

            long number = strtol(num_str, NULL, 10);
            printf("Number: %ld, Position: %zu\n", number, start);

            free(num_str);
            num_str = NULL;
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *input = "abc123def4567gh89i0";
    print_numbers_and_positions(input);
    return 0;
}