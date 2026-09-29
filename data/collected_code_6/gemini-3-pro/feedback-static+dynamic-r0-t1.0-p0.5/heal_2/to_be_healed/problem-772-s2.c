#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t secure_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void remove_words_of_length_k(char *str, size_t max_len, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    size_t len = secure_strlen(str, max_len);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    size_t i = 0;
    size_t j = 0;
    size_t word_start = 0;
    int word_len = 0;

    while (i <= len) {
        if (i < len && str[i] != '\0' && !isspace((unsigned char)str[i])) {
            if (word_len == 0) {
                word_start = i;
            }
            word_len++;
        } else {
            if (word_len > 0) {
                if (word_len != k) {
                    if (j > 0 && result[j - 1] != ' ' && word_start > 0 && str[word_start - 1] == ' ') {
                        result[j++] = ' ';
                    }
                    for (int w = 0; w < word_len; w++) {
                        result[j++] = str[word_start + w];
                    }
                }
                word_len = 0;
            }
            if (i < len && str[i] != '\0' && isspace((unsigned char)str[i])) {
                if (j == 0 || result[j - 1] != ' ') {
                    result[j++] = str[i];
                }
            }
        }
        i++;
    }

    if (j > 0 && isspace((unsigned char)result[j - 1])) {
        j--;
    }
    result[j] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, j + 1);
    free(result);
}

int main(void) {
    size_t buffer_size = 256;
    char *str = (char *)malloc(buffer_size);
    if (str == NULL) {
        return 1;
    }
    int k;

    if (fgets(str, (int)buffer_size, stdin) != NULL) {
        size_t len = secure_strlen(str, buffer_size);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (scanf("%d", &k) == 1) {
            remove_words_of_length_k(str, buffer_size, k);
            printf("%s\n", str);
        }
    }

    free(str);
    return 0;
}