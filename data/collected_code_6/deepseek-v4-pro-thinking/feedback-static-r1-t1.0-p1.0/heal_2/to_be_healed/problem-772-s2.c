#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k <= 0) {
        return;
    }

    char *read = str;
    char *write = str;
    char * const end = str + size;
    int first_kept = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end && *read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read != '\0' && isspace((unsigned char)*read)) {
            read++;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= end || *read == '\0') {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        char *word_start = read;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read != '\0' && !isspace((unsigned char)*read)) {
            read++;
        }

        int word_length = (int)(read - word_start);

        if (word_length != k) {
            if (!first_kept) {
                if (write < end) {
                    *write++ = ' ';
                }
            }

            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (word_start < read && write < end) {
                *write++ = *word_start++;
            }

            first_kept = 0;
        }
    }

    if (write < end) {
        *write = '\0';
    } else if (end > str) {
        *(end - 1) = '\0';
    }
}

int main(void) {
    char text[] = "this is a simple test string";
    remove_words_of_length(text, sizeof(text), 2);
    printf("%s\n", text);
    return 0;
}