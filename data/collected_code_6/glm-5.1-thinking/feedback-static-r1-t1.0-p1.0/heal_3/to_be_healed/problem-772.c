#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

char *remove_words_of_length(char *str, size_t size, size_t k) {
    if (str == NULL || size == 0) {
        return str;
    }

    char *read = str;
    char *write = str;
    const char *end = str + size;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end && *read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read != '\0' && isspace((unsigned char)*read)) {
            *write++ = *read++;
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
        const char *word_start = read;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read != '\0' && !isspace((unsigned char)*read)) {
            read++;
        }

        size_t word_len = read - word_start;

        if (word_len != k) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (word_start < read) {
                *write++ = *word_start++;
            }
        }
    }

    if (write < end) {
        *write = '\0';
    } else {
        str[size - 1] = '\0';
    }

    return str;
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: %s\n", str1);
    remove_words_of_length(str1, sizeof(str1), 4);
    printf("Modified: %s\n", str1);

    char str2[] = "Hello \t world \n from C programming";
    printf("Original: %s\n", str2);
    remove_words_of_length(str2, sizeof(str2), 5);
    printf("Modified: %s\n", str2);

    return 0;
}