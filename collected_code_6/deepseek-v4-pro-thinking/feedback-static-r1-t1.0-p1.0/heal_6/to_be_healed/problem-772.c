#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

void remove_words_of_length(char *str, size_t buf_size, int k) {
    if (str == NULL || buf_size == 0 || k <= 0) {
        return;
    }

    size_t read = 0;
    size_t write = 0;
    int has_word = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < buf_size && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < buf_size && str[read] != '\0' && isspace((unsigned char)str[read])) {
            read++;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= buf_size || str[read] == '\0') {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t word_start = read;
        size_t word_len = 0;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < buf_size && str[read] != '\0' && !isspace((unsigned char)str[read])) {
            read++;
            word_len++;
        }

        if (word_len != (size_t)k) {
            if (has_word) {
                if (write < buf_size - 1) {
                    str[write++] = ' ';
                }
            }

            size_t avail = buf_size - write;
            if (word_len <= avail) {
                memmove(&str[write], &str[word_start], word_len);
                write += word_len;
            } else {
                if (avail > 0) {
                    memmove(&str[write], &str[word_start], avail);
                    write += avail;
                }
                break;
            }
            has_word = 1;
        }
    }

    if (write < buf_size) {
        str[write] = '\0';
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