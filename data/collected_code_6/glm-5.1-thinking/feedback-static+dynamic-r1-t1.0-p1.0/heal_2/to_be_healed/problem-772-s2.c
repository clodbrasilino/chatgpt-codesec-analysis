#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t bufsize, size_t k) {
    if (!str || bufsize == 0) {
        return;
    }

    char *read = str;
    char *write = str;
    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *end = str + bufsize;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end && *read != '\0') {
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
            while (read < end && *read != '\0' && isalpha((unsigned char)*read)) {
                length++;
                read++;
            }

            if (length != k) {
                size_t remaining = end - write - 1;
                size_t copy_len = length > remaining ? remaining : length;
                if (copy_len > 0) {
                    memmove(write, start, copy_len);
                    write += copy_len;
                }
            }
        } else {
            if (write < end - 1) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                *write = *read;
                write++;
            }
            read++;
        }
    }

    *write = '\0';
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    size_t k = 3;

    printf("Before: %s\n", text);
    remove_words_of_length(text, sizeof(text), k);
    printf("After: %s\n", text);

    return 0;
}