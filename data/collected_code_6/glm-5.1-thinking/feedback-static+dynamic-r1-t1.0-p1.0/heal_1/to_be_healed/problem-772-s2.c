#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t k) {
    if (str == NULL) {
        return;
    }

    char *read = str;
    char *write = str;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (isalpha((unsigned char)*read)) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            char *start = read;
            size_t length = 0;

            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (*read != '\0' && isalpha((unsigned char)*read)) {
                length++;
                read++;
            }

            if (length != k) {
                memmove(write, start, length);
                write += length;
            }
        } else {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            *write = *read;
            write++;
            read++;
        }
    }

    *write = '\0';
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    size_t k = 3;

    printf("Before: %s\n", text);
    remove_words_of_length(text, k);
    printf("After: %s\n", text);

    return 0;
}