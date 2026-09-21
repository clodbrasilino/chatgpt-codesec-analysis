#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

char *remove_words_of_length(char *str, int k) {
    if (str == NULL || k < 0) {
        return str;
    }

    char *read = str;
    char *write = str;
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *end = str + strlen(str);

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && isspace((unsigned char)*read)) {
            *write++ = *read++;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= end) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        char *word_start = read;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && !isspace((unsigned char)*read)) {
            read++;
        }

        size_t word_len = read - word_start;

        if (word_len != (size_t)k) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (word_start < read) {
                *write++ = *word_start++;
            }
        }
    }

    *write = '\0';
    return str;
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: %s\n", str1);
    remove_words_of_length(str1, 4);
    printf("Modified: %s\n", str1);

    char str2[] = "Hello \t world \n from C programming";
    printf("Original: %s\n", str2);
    remove_words_of_length(str2, 5);
    printf("Modified: %s\n", str2);

    return 0;
}