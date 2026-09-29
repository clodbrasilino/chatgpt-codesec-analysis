#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t bufsiz, size_t k) {
    if (str == NULL || bufsiz == 0) {
        return;
    }

    const char *read = str;
    char *write = str;
    const char *end = str + bufsiz;

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
            const char *start = read;
            size_t length = 0;

            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (read < end && *read != '\0' && isalpha((unsigned char)*read)) {
                length++;
                read++;
            }

            if (length != k) {
                for (size_t i = 0; i < length; i++) {
                    if (write < end - 1) {
                        *write++ = start[i];
                    }
                }
            }
        } else {
            if (write < end - 1) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                *write++ = *read;
            }
            read++;
        }
    }

    if (write < end) {
        *write = '\0';
    }
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    size_t k = 3;

    printf("Before: %s\n", text);
    remove_words_of_length(text, sizeof(text), k);
    printf("After: %s\n", text);

    return 0;
}