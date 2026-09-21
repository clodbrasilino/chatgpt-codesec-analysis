#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str, size_t max_length) {
    char *write = str;
    char *read = str;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0' && (size_t)(read - str) < max_length) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!isdigit((unsigned char)*read)) {
            if ((size_t)(write - str) < max_length - 1) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                *write++ = *read;
            }
        }
        read++;
    }
    *write = '\0';
}

int main() {
    char strings[][20] = {"hello123", "world4567", "test890"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);
    size_t max_length = sizeof(strings[0]) - 1;

    for (int i = 0; i < num_strings; i++) {
        remove_digits(strings[i], max_length);
        printf("%s\n", strings[i]);
    }

    return 0;
}