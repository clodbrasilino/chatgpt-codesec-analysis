#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void remove_words_of_length_k(char *str, size_t k, size_t size) {
    if (str == NULL || k == 0 || size == 0) {
        return;
    }

    char *read = str;
    char *write = str;
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *end = str + size;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end && *read) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read && isspace((unsigned char)*read)) {
            read++;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= end || !*read) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        char *word_start = read;

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < end && *read && !isspace((unsigned char)*read)) {
            read++;
        }

        size_t word_len = (size_t)(read - word_start);

        if (word_len != k) {
            if (write != str) {
                if (write < end) {
                    *write++ = ' ';
                } else {
                    break;
                }
            }
            size_t space_left = (size_t)(end - write);
            size_t copy_len = word_len < space_left ? word_len : space_left;
            memmove(write, word_start, copy_len);
            write += copy_len;
        }
    }

    if (write < end) {
        *write = '\0';
    } else {
        str[size - 1] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[64] = "This is a test string for removing words";
    size_t k = 4;

    printf("Original: \"%s\"\n", str);
    remove_words_of_length_k(str, k, sizeof(str));
    printf("Modified: \"%s\"\n", str);

    return 0;
}