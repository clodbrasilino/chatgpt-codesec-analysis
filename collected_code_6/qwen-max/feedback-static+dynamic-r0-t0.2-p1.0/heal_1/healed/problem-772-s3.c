#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    char *token;
    char *temp = strdup(str);
    int capacity = 0;
    int len = 0;

    token = strtok(temp, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            int token_len = strlen(token);
            int new_len = len + token_len + 1;
            if (new_len > capacity) {
                result = realloc(result, new_len + 1);
                if (result == NULL) {
                    free(temp);
                    return NULL;
                }
                capacity = new_len + 1;
            }
            memcpy(result + len, token, token_len);
            result[new_len - 1] = ' ';
            len = new_len;
        }
        token = strtok(NULL, " ");
    }

    if (len > 0) {
        result[len - 1] = '\0';
        result = realloc(result, len);
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
    char str[] = "This is a test string with some words of length five";
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