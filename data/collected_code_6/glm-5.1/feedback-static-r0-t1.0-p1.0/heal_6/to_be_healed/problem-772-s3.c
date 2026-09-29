#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

void remove_words_of_length_k(char *str, size_t k) {
    if (str == NULL || k == 0) {
        return;
    }

    char *read = str;
    char *write = str;
    size_t len = strnlen(str, SIZE_MAX);
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char * const end = str + len;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && isspace((unsigned char)*read)) {
            read++;
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
        char * const word_start = read;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && !isspace((unsigned char)*read)) {
            read++;
        }

        size_t word_len = (size_t)(read - word_start);

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
    char str[] = "This is a test string for removing words";
    size_t k = 4;

    printf("Original: \"%s\"\n", str);
    remove_words_of_length_k(str, k);
    printf("Modified: \"%s\"\n", str);

    return 0;
}