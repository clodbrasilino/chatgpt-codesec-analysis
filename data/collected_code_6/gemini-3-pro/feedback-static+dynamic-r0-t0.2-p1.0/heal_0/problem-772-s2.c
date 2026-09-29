#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    int i = 0;
    int j = 0;
    int word_start = 0;
    int word_len = 0;

    while (i <= len) {
        if (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            if (word_len == 0) {
                word_start = i;
            }
            word_len++;
        } else {
            if (word_len > 0) {
                if (word_len != k) {
                    for (int w = word_start; w < word_start + word_len; w++) {
                        result[j++] = str[w];
                    }
                }
                word_len = 0;
            }
            if (str[i] != '\0') {
                if (j == 0 || result[j - 1] != ' ' || str[i] != ' ') {
                    result[j++] = str[i];
                }
            }
        }
        i++;
    }

    result[j] = '\0';

    int end = j - 1;
    while (end >= 0 && isspace((unsigned char)result[end])) {
        result[end] = '\0';
        end--;
    }

    int start = 0;
    while (result[start] != '\0' && isspace((unsigned char)result[start])) {
        start++;
    }

    if (start > 0) {
        memmove(result, result + start, strlen(result + start) + 1);
    }

    strcpy(str, result);
    free(result);
}

int main() {
    char str[256];
    int k;

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strlen(str);
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