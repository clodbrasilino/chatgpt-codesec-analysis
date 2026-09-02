#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(char *str, int k) {
    char *token = strtok(str, " ");
    char *new_str = NULL;
    char *temp_str = NULL;
    const char s[2] = " ";

    while (token != NULL) {
        if (strlen(token) != k) {
            if (new_str == NULL) {
                new_str = malloc(strlen(token) + 1);
                strcpy(new_str, token);
            } else {
                temp_str = realloc(new_str, strlen(new_str) + strlen(token) + 2);
                if (temp_str == NULL) {
                    free(new_str);
                    return NULL;
                }
                new_str = temp_str;
                strcat(new_str, s);
                strcat(new_str, token);
            }
        }
        token = strtok(NULL, " ");
    }

    return new_str ? new_str : strdup("");
}

int main() {
    char str[] = "This is a test string with some words of various lengths";
    int k = 2;
    char *result = remove_k_length_words(str, k);

    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}