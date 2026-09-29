#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_words_of_length_k(char *str, size_t bufsize, int k) {
    if (str == NULL || bufsize == 0 || k <= 0) {
        return;
    }

    size_t read = 0;
    size_t write = 0;
    int has_word = 0;

    while (read < bufsize && str[read] != '\0') {
        while (read < bufsize && str[read] != '\0' && isspace((unsigned char)str[read])) {
            read++;
        }
        if (read >= bufsize || str[read] == '\0') {
            break;
        }

        size_t word_start = read;
        while (read < bufsize && str[read] != '\0' && !isspace((unsigned char)str[read])) {
            read++;
        }

        size_t word_len = read - word_start;
        if (word_len != (size_t)k) {
            if (has_word) {
                if (write + 1 < bufsize) {
                    str[write++] = ' ';
                } else {
                    break;
                }
            }

            if (write + word_len < bufsize) {
                memmove(str + write, str + word_start, word_len);
                write += word_len;
                has_word = 1;
            } else {
                size_t remaining = bufsize - write - 1;
                if (remaining > 0) {
                    memmove(str + write, str + word_start, remaining);
                    write += remaining;
                }
                break;
            }
        }
    }

    if (write < bufsize) {
        str[write] = '\0';
    } else {
        str[bufsize - 1] = '\0';
    }
}

int main(void) {
    char str[] = "  hello   world  is  a test  ";
    remove_words_of_length_k(str, sizeof(str), 2);
    printf("%s\n", str);
    return 0;
}