#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    char *result = NULL;
    size_t result_len = 0;
    char *token = strtok((char *)str, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            if (result == NULL) {
                result = strdup(token);
                if (result) result_len = strlen(result);
            } else {
                size_t new_len = result_len + 1 + strlen(token) + 1;
                char *new_result = realloc(result, new_len);
                if (new_result) {
                    result = new_result;
                    strcat(result, " ");
                    strcat(result, token);
                    result_len = new_len - 1;
                } else {
                    free(result);
                    return NULL;
                }
            }
        }
        token = strtok(NULL, " ");
    }
    return result ? result : strdup("");
}

int main() {
    const char str[] = "This is a test string with some words of length five";
    int k = 5;
    char *new_str = remove_k_length_words(str, k);
    printf("%s\n", new_str);
    free(new_str);
    return 0;
}