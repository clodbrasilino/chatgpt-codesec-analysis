#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    size_t read = 0;
    size_t write = 0;
    size_t len = strlen(str);
    int has_word = 0;

    while (read < len) {
        while (read < len && isspace((unsigned char)str[read])) {
            read++;
        }

        if (read >= len) {
            break;
        }

        size_t word_start = read;

        while (read < len && !isspace((unsigned char)str[read])) {
            read++;
        }

        size_t word_len = read - word_start;

        if (word_len != (size_t)k) {
            if (has_word) {
                str[write++] = ' ';
            }

            memmove(str + write, str + word_start, word_len);
            write += word_len;
            has_word = 1;
        }
    }

    str[write] = '\0';
}

int main(void) {
    char str[] = "  hello   world  is  a test  ";

    remove_words_of_length_k(str, 2);

    printf("%s\n", str);

    return 0;
}