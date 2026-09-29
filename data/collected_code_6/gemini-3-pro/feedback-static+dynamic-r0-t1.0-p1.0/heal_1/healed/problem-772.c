#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words_of_length_k(char *str, size_t k) {
    if (str == NULL || k == 0) {
        return;
    }

    size_t i = 0;
    size_t write_idx = 0;

    while (str[i] != '\0') {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            str[write_idx++] = str[i++];
            continue;
        }

        size_t word_start = i;
        while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            i++;
        }
        
        size_t word_len = i - word_start;

        if (word_len != k) {
            for (size_t j = word_start; j < i; j++) {
                str[write_idx++] = str[j];
            }
        }
    }

    str[write_idx] = '\0';
}

int main(void) {
    size_t buf_size = 256;
    char *str = (char *)malloc(buf_size);
    if (str == NULL) {
        return 1;
    }

    size_t k;

    if (fgets(str, buf_size, stdin) != NULL) {
        size_t len = strnlen(str, buf_size);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (scanf("%zu", &k) == 1) {
            remove_words_of_length_k(str, k);
            printf("%s\n", str);
        }
    }

    free(str);
    return 0;
}