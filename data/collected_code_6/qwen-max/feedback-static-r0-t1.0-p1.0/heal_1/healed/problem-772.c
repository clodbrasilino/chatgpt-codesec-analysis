#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_k_length_words(const char *str, int k) {
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    result[0] = '\0';
    
    const char *token = strtok((char*)str, " ");
    while (token != NULL) {
        size_t token_len = strlen(token);
        if (token_len != k) {
            strncat(result, token, len - strlen(result));
            strncat(result, " ", 1);
        }
        token = strtok(NULL, " ");
    }
    
    size_t result_len = strlen(result);
    if (result_len > 0 && result[result_len - 1] == ' ') {
        result[result_len - 1] = '\0';
    }
    
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