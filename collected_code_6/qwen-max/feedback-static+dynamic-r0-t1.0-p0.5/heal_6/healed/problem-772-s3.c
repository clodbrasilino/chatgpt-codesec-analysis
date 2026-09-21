#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    char *copy = strdup(str);
    if (copy == NULL) {
        return NULL;
    }

    char *token;
    char *result = NULL;
    size_t result_len = 0;

    token = strtok(copy, " ");
    while (token != NULL) {
        size_t token_len = strlen(token);
        if (token_len != (size_t)k) {
            size_t new_result_len = result_len + token_len + 1;
            char *new_result = realloc(result, new_result_len);
            if (new_result) {
                result = new_result;
                if (result_len > 0) {
                    result[result_len++] = ' ';
                }
                memcpy(result + result_len, token, token_len);
                result_len += token_len;
                result[result_len] = '\0';
            } else {
                free(result);
                result = NULL;
                break;
            }
        }
        token = strtok(NULL, " ");
    }

    free(copy);

    if (result == NULL) {
        result = strdup("");
    }

    return result;
}

int main() {
    const char str[] = "This is a test string with some words of different lengths";
    int k = 4;
    char *new_str = remove_k_length_words(str, k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }
    return 0;
}