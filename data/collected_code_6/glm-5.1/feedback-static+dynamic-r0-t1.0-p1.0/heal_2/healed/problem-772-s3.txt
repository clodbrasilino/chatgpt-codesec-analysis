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
    char *end = str + size;

    while (read < end && *read) {
        while (read < end && *read && isspace((unsigned char)*read)) {
            read++;
        }

        if (read >= end || !*read) {
            break;
        }

        char *word_start = read;

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
    char str[64] = "This is a test string for removing words";
    size_t k = 4;

    printf("Original: \"%s\"\n", str);
    remove_words_of_length_k(str, k, sizeof(str));
    printf("Modified: \"%s\"\n", str);

    return 0;
}