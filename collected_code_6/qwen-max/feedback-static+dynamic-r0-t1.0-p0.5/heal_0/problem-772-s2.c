#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            if (result == NULL) {
                result = strdup(token);
            } else {
                size_t len1 = strlen(result);
                result = realloc(result, len1 + 1 + strlen(token) + 1);
                if (result) {
                    strcat(result, " ");
                    strcat(result, token);
                }
            }
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