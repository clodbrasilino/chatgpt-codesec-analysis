#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void remove_words_of_length_k(char *str, size_t k) {
    if (str == NULL || k == 0) {
        return;
    }

    char *read = str;
    char *write = str;
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *end = str + strnlen(str, SIZE_MAX);

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
        size_t word_len = 0;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read != '\0' && !isspace((unsigned char)*read)) {
            read++;
            word_len++;
        }

        if (word_len != k) {
            if (write != str) {
                *write++ = ' ';
            }
            memmove(write, word_start, word_len);
            write += word_len;
        }
    }

    *write = '\0';
}

int main() {
    size_t buffer_size = 64;
    char *str = malloc(buffer_size);
    if (str == NULL) {
        return 1;
    }
    snprintf(str, buffer_size, "%s", "This is a test string for removing words");
    size_t k = 4;

    printf("Original: \"%s\"\n", str);
    remove_words_of_length_k(str, k);
    printf("Modified: \"%s\"\n", str);

    free(str);
    return 0;
}