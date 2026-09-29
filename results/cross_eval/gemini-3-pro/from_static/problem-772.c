#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void remove_words_of_length_k(char *str, size_t max_len, size_t k) {
    if (str == NULL || k == 0 || max_len == 0) {
        return;
    }

    size_t len = strnlen(str, max_len);
    size_t result_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            str[result_idx++] = str[i++];
            continue;
        }

        size_t word_start = i;
        while (i < len && str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            i++;
        }
        size_t word_len = i - word_start;

        if (word_len != k) {
            for (size_t j = word_start; j < i; j++) {
                str[result_idx++] = str[j];
            }
        }
    }

    if (result_idx < max_len) {
        str[result_idx] = '\0';
    }
}

int main(void) {
    char *str = NULL;
    size_t buf_size = 0;
    size_t k;

    ssize_t read_len = getline(&str, &buf_size, stdin);
    if (read_len != -1) {
        if (read_len > 0 && str[read_len - 1] == '\n') {
            str[read_len - 1] = '\0';
        }

        if (scanf("%zu", &k) == 1) {
            remove_words_of_length_k(str, buf_size, k);
            printf("%s\n", str);
        }
    }

    free(str);
    return 0;
}