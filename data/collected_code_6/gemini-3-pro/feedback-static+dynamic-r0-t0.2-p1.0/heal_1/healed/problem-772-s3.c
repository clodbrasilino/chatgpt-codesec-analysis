#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    int read_idx = 0;
    int write_idx = 0;
    int word_start = 0;
    int word_len = 0;
    int is_first = 1;

    while (str[read_idx] != '\0') {
        while (str[read_idx] == ' ') {
            read_idx++;
        }
        
        if (str[read_idx] == '\0') {
            break;
        }

        word_start = read_idx;
        while (str[read_idx] != ' ' && str[read_idx] != '\0') {
            read_idx++;
        }
        
        word_len = read_idx - word_start;

        if (word_len != k) {
            if (!is_first) {
                str[write_idx++] = ' ';
            }
            for (int i = 0; i < word_len; i++) {
                str[write_idx++] = str[word_start + i];
            }
            is_first = 0;
        }
    }
    str[write_idx] = '\0';
}

int main(void) {
    char str[256];
    int k;

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = 0;
        while (len < sizeof(str) && str[len] != '\0') {
            len++;
        }
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (scanf("%d", &k) == 1) {
            remove_words_of_length_k(str, k);
            printf("%s\n", str);
        }
    }

    return 0;
}