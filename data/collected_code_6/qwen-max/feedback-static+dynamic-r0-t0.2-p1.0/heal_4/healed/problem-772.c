#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    char *result = NULL;
    size_t result_len = 0;
    const char *p = str;
    while (*p) {
        const char *start = p;
        while (*p && *p != ' ') p++;
        if (p - start != k) {
            size_t token_len = p - start;
            char *tmp = realloc(result, result_len + token_len + (result ? 1 : 0) + 1);
            if (tmp == NULL) {
                free(result);
                return NULL;
            }
            if (result && result_len > 0) {
                tmp[result_len++] = ' ';
            }
            for (size_t i = 0; i < token_len; i++) {
                tmp[result_len + i] = start[i];
            }
            result_len += token_len;
            tmp[result_len] = '\0';
            result = tmp;
        }
        if (*p == ' ') p++;
    }
    if (result == NULL) {
        result = strdup("");
    }
    return result;
}

int main() {
    const char *str = "This is a test string with some words of length five";
    int k = 5;
    char *new_str = remove_k_length_words(str, k);
    printf("%s\n", new_str);
    free(new_str);
    return 0;
}