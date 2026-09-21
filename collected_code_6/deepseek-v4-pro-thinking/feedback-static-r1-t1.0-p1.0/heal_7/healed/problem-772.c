#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

void remove_words_of_length(char *str, size_t buf_size, int k) {
    if (str == NULL || buf_size == 0 || k <= 0) return;

    size_t uk = (size_t)k;
    const char *end = str + buf_size;
    char *read_ptr = str;
    char *write_ptr = str;
    int has_word = 0;

    while (read_ptr < end && *read_ptr != '\0') {
        while (read_ptr < end && *read_ptr != '\0' && isspace((unsigned char)*read_ptr)) {
            read_ptr++;
        }
        if (read_ptr >= end || *read_ptr == '\0') break;

        char *word_start = read_ptr;
        size_t word_len = 0;
        while (read_ptr < end && *read_ptr != '\0' && !isspace((unsigned char)*read_ptr)) {
            read_ptr++;
            word_len++;
        }

        if (word_len != uk) {
            if (has_word) {
                if (write_ptr + 1 < end) {
                    *write_ptr++ = ' ';
                } else {
                    break;
                }
            }

            size_t avail = (size_t)(end - write_ptr);
            if (word_len <= avail) {
                memmove(write_ptr, word_start, word_len);
                write_ptr += word_len;
            } else {
                if (avail > 0) {
                    memmove(write_ptr, word_start, avail);
                    write_ptr += avail;
                }
                break;
            }
            has_word = 1;
        }
    }

    if (write_ptr < end) {
        *write_ptr = '\0';
    } else if (end > str) {
        *(end - 1) = '\0';
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