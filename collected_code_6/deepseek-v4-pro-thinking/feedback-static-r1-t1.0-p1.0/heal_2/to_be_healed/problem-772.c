#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_words_of_length(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    char *read = str;
    char *write = str;
    int has_word = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t skip = strspn(read, " \t\n\r\f\v");
        read += skip;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (!*read) break;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t word_len = strcspn(read, " \t\n\r\f\v");
        if (word_len != (size_t)k) {
            if (has_word) {
                *write++ = ' ';
            }
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            memmove(write, read, word_len);
            write += word_len;
            has_word = 1;
        }
        read += word_len;
    }

    *write = '\0';
}

int main(void) {
    char str[] = "This is a sample string with several words";
    int k = 2;

    printf("Original: %s\n", str);
    remove_words_of_length(str, k);
    printf("Modified: %s\n", str);

    return 0;
}