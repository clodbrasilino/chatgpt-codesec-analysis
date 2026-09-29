#include <ctype.h>
#include <stdio.h>

void remove_words_of_length(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    char *read = str;
    char *write = str;
    int first_kept = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (*read != '\0' && isspace((unsigned char)*read)) {
            read++;
        }

        if (*read == '\0') {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        char *word_start = read;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (*read != '\0' && !isspace((unsigned char)*read)) {
            read++;
        }

        int word_length = (int)(read - word_start);

        if (word_length != k) {
            if (!first_kept) {
                *write++ = ' ';
            }

            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (word_start < read) {
                *write++ = *word_start++;
            }

            first_kept = 0;
        }
    }

    *write = '\0';
}

int main(void) {
    char text[] = "this is a simple test string";
    remove_words_of_length(text, 2);
    printf("%s\n", text);
    return 0;
}