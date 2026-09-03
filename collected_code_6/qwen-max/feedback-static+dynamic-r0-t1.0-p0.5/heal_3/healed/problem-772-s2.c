#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    size_t result_len = 0;
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            size_t token_len = strlen(token);
            result = realloc(result, result_len + token_len + 2);
            if (result == NULL) break;
            if (result_len > 0) result[result_len++] = ' ';
            memcpy(result + result_len, token, token_len);
            result_len += token_len;
            result[result_len] = '\0';
        }
        token = strtok(NULL, " ");
    }
    return result;
}

int main() {
    char str[] = "This is a test string with some words of length four";
    int k = 4;
    char *new_str = remove_k_length_words(str, k);
    if (new_str) {
        printf("%s\n", new_str);
        free(new_str);
    }
    return 0;
}