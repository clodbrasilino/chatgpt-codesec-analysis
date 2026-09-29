#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_words_of_length_k(char *str, size_t k) {
    if (str == NULL || k == 0) {
        return;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    size_t result_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            result[result_idx++] = str[i++];
            continue;
        }

        size_t word_start = i;
        while (i < len && str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            i++;
        }
        size_t word_len = i - word_start;

        if (word_len != k) {
            for (size_t j = word_start; j < i; j++) {
                result[result_idx++] = str[j];
            }
        }
    }

    result[result_idx] = '\0';
    strcpy(str, result);
    free(result);
}

int main(void) {
    char str[256];
    size_t k;

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (scanf("%zu", &k) == 1) {
            remove_words_of_length_k(str, k);
            printf("%s\n", str);
        }
    }

    return 0;
}