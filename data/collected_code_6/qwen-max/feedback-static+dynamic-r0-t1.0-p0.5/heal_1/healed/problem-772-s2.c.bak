#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            size_t len1 = result ? strlen(result) : 0;
            char *new_result = realloc(result, len1 + 1 + strlen(token) + 1);
            if (new_result) {
                result = new_result;
                if (len1 > 0) strcat(result, " ");
                strcat(result, token);
            } else {
                free(result);
                result = NULL;
                break;
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