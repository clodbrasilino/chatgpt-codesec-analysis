#include <stdio.h>
#include <stdlib.h>

char* remove_k_length_words(const char *str, int k) {
    size_t len = 0;
    for (const char *s = str; *s; s++) len++;
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';

    const char *token;
    char *saveptr;

    for (const char *s = str; (token = strtok_r((char*)s, " ", &saveptr)) != NULL; s = NULL) {
        size_t token_len = 0;
        for (const char *t = token; *t; t++) token_len++;

        if (token_len != k) {
            size_t result_len = 0;
            for (const char *r = result; *r; r++) result_len++;

            if (result_len + token_len + 1 <= len + 1) {
                for (size_t i = 0; i < token_len; i++) result[result_len + i] = token[i];
                result[result_len + token_len] = ' ';
                result[result_len + token_len + 1] = '\0';
            }
        }
    }

    size_t result_len = 0;
    for (const char *r = result; *r; r++) result_len++;

    if (result_len > 0 && result[result_len - 1] == ' ') {
        result[result_len - 1] = '\0';
    }

    return result;
}

int main() {
    const char str[] = "this is a test string with some words of different lengths";
    int k = 2;
    char *new_str = remove_k_length_words(str, k);

    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}