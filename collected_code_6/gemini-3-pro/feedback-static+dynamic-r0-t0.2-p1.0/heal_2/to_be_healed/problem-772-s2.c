#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, size_t max_size, int k) {
    if (str == NULL || k <= 0 || max_size == 0) {
        return;
    }

    size_t len = 0;
    while (len < max_size && str[len] != '\0') {
        len++;
    }

    if (len == max_size && str[max_size - 1] != '\0') {
        return;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    size_t i = 0;
    size_t j = 0;
    size_t word_start = 0;
    int word_len = 0;

    while (i <= len) {
        if (i < len && !isspace((unsigned char)str[i])) {
            if (word_len == 0) {
                word_start = i;
            }
            word_len++;
        } else {
            if (word_len > 0) {
                if (word_len != k) {
                    for (size_t w = word_start; w < word_start + word_len; w++) {
                        result[j++] = str[w];
                    }
                }
                word_len = 0;
            }
            if (i < len) {
                if (j == 0 || result[j - 1] != ' ' || str[i] != ' ') {
                    result[j++] = str[i];
                }
            }
        }
        i++;
    }

    result[j] = '\0';

    int end = (int)j - 1;
    while (end >= 0 && isspace((unsigned char)result[end])) {
        result[end] = '\0';
        end--;
    }

    size_t start = 0;
    while (result[start] != '\0' && isspace((unsigned char)result[start])) {
        start++;
    }

    if (start > 0) {
        size_t rem_len = 0;
        while (result[start + rem_len] != '\0') {
            rem_len++;
        }
        memmove(result, result + start, rem_len + 1);
    }

    snprintf(str, max_size, "%s", result);
    free(result);
}

int main(void) {
    size_t buf_size = 256;
    char *str = (char *)malloc(buf_size);
    if (str == NULL) {
        return 1;
    }
    
    int k;

    if (fgets(str, (int)buf_size, stdin) != NULL) {
        size_t len = 0;
        while (len < buf_size && str[len] != '\0') {
            len++;
        }
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            /* Possible weaknesses found:
             *  Variable 'len' is assigned a value that is never used. [unreadVariable]
             */
            len--;
        }

        if (scanf("%d", &k) == 1) {
            remove_words_of_length_k(str, buf_size, k);
            printf("%s\n", str);
        }
    }

    free(str);
    return 0;
}