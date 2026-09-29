#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

void remove_words_of_length(char *str, size_t buf_size, int k) {
    if (str == NULL || buf_size == 0 || k <= 0) {
        return;
    }

    char *read = str;
    char *write = str;
    int has_word = 0;
    const char *const end = str + buf_size - 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read <= end && *read) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read <= end && *read && isspace((unsigned char)*read)) {
            read++;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read > end || !*read) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        const char *word_start = read;
        size_t word_len = 0;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read <= end && *read && !isspace((unsigned char)*read)) {
            read++;
            word_len++;
        }

        if (word_len != (size_t)k) {
            if (has_word) {
                if (write < end) {
                    *write++ = ' ';
                }
            }
            if (write + word_len <= (size_t)(end - write + 1)) {
                memmove(write, word_start, word_len);
                write += word_len;
            } else {
                size_t avail = (size_t)(end - write + 1);
                if (avail > 0) {
                    memmove(write, word_start, avail);
                    write += avail;
                }
                break;
            }
            has_word = 1;
        }
    }

    if (write <= end) {
        *write = '\0';
    } else {
        str[buf_size - 1] = '\0';
    }
}

int main(void) {
    char str[] = "This is a sample string with several words";
    int k = 2;

    printf("Original: %s\n", str);
    remove_words_of_length(str, sizeof(str), k);
    printf("Modified: %s\n", str);

    return 0;
}