#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_words_of_length_k(char *str, size_t bufsize, int k) {
    if (str == NULL || bufsize == 0 || k <= 0) {
        return;
    }

    size_t read = 0;
    size_t write = 0;
    int need_separator = 0;

    while (read < bufsize) {
        if (str[read] == '\0') {
            break;
        }
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
            if (need_separator) {
                if (write + 1 < bufsize) {
                    str[write++] = ' ';
                } else {
                    break;
                }
            }
            size_t room = bufsize - write;
            if (word_len < room) {
                memmove(str + write, str + word_start, word_len);
                write += word_len;
                need_separator = 1;
            } else {
                if (room > 1) {
                    memmove(str + write, str + word_start, room - 1);
                    write += room - 1;
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