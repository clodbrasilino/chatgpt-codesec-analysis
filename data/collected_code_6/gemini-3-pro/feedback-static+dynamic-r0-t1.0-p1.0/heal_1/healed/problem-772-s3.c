#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, size_t max_len, int k) {
    if (str == NULL || k <= 0 || max_len == 0) {
        return;
    }

    size_t len = strnlen(str, max_len);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    size_t result_idx = 0;
    size_t word_start = 0;
    int in_word = 0;

    for (size_t i = 0; i <= len; i++) {
        if (!isspace((unsigned char)str[i]) && str[i] != '\0') {
            if (!in_word) {
                word_start = i;
                in_word = 1;
            }
        } else {
            if (in_word) {
                size_t word_len = i - word_start;
                if (word_len != (size_t)k) {
                    for (size_t j = word_start; j < i; j++) {
                        result[result_idx++] = str[j];
                    }
                }
                in_word = 0;
            }
            if (str[i] != '\0') {
                if (result_idx > 0 && result[result_idx - 1] != ' ') {
                    result[result_idx++] = str[i];
                } else if (isspace((unsigned char)str[i]) && str[i] != ' ') {
                     result[result_idx++] = str[i];
                }
            }
        }
    }

    result[result_idx] = '\0';

    size_t final_idx = 0;
    int space_found = 1;
    for (size_t i = 0; i < result_idx; i++) {
        if (result[i] == ' ') {
            if (!space_found) {
                str[final_idx++] = result[i];
                space_found = 1;
            }
        } else {
            str[final_idx++] = result[i];
            space_found = 0;
        }
    }

    if (final_idx > 0 && str[final_idx - 1] == ' ') {
        final_idx--;
    }
    str[final_idx] = '\0';

    free(result);
}

int main(void) {
    char *str = NULL;
    size_t buf_size = 0;
    ssize_t read_len;
    int k;

    read_len = getline(&str, &buf_size, stdin);
    if (read_len != -1) {
        if (read_len > 0 && str[read_len - 1] == '\n') {
            str[read_len - 1] = '\0';
        }

        if (scanf("%d", &k) == 1) {
            remove_words_of_length_k(str, buf_size, k);
            printf("%s\n", str);
        }
    }

    free(str);
    return 0;
}