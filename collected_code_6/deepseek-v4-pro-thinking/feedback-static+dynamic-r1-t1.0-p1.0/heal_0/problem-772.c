#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_words_of_length(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    char *read = str;
    char *write = str;
    int has_word = 0;
    size_t word_len = 0;

    while (*read != '\0') {
        while (*read != '\0' && isspace((unsigned char)*read)) {
            read++;
        }

        if (*read == '\0') {
            break;
        }

        char *word_start = read;
        word_len = 0;

        while (*read != '\0' && !isspace((unsigned char)*read)) {
            read++;
            word_len++;
        }

        if (word_len != (size_t)k) {
            if (has_word) {
                *write++ = ' ';
            }
            memmove(write, word_start, word_len);
            write += word_len;
            has_word = 1;
        }
    }

    *write = '\0';
}

int main(void) {
    char str[] = "This is a sample string with several words";
    int k = 2;

    printf("Original: %s\n", str);
    remove_words_of_length(str, k);
    printf("Modified: %s\n", str);

    return 0;
}