#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char str[256];
    size_t k;

    memset(str, 0, sizeof(str));

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, sizeof(str));
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (scanf("%zu", &k) == 1) {
            remove_words_of_length_k(str, sizeof(str), k);
            printf("%s\n", str);
        }
    }

    return 0;
}