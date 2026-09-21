#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    char *result = NULL;
    char *token;
    char *temp = strdup(str);
    int len = 0;

    token = strtok(temp, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            size_t token_len = strlen(token) + 1;
            result = realloc(result, len + token_len + 1);
            if (result == NULL) {
                free(temp);
                return NULL;
            }
            memcpy(result + len, token, token_len);
            len += token_len - 1; // Exclude the null terminator
            result[len] = ' ';
            len++;
        }
        token = strtok(NULL, " ");
    }

    if (len > 0) {
        result[len - 1] = '\0';
    } else {
        result = realloc(result, 1);
        if (result == NULL) {
            free(temp);
            return NULL;
        }
        *result = '\0';
    }

    free(temp);
    return result;
}

int main() {
    const char str[] = "This is a test string with some words of length five";
    int k = 5;
    char *new_str = remove_k_length_words(str, k);

    if (new_str != NULL) {
        printf("%s\n", new_str);
        free(new_str);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}