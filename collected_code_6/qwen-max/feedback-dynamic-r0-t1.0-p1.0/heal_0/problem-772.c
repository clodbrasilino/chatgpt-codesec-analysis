#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(char *str, int k) {
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';
    
    char *token = strtok(str, " ");
    while (token != NULL) {
        if (strlen(token) != k) {
            strncat(result, token, len);
            strncat(result, " ", 1);
        }
        token = strtok(NULL, " ");
    }
    
    if (result[strlen(result) - 1] == ' ') {
        result[strlen(result) - 1] = '\0';
    }
    
    free(str);
    return result;
}

int main() {
    char str[] = "this is a test string with some words of different lengths";
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