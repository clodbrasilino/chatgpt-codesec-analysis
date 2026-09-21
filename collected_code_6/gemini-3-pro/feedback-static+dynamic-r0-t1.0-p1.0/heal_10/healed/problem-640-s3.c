#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    char* buffer = NULL;
    size_t bufsize = 0;
    ssize_t read_len;

    read_len = getline(&buffer, &bufsize, stdin);
    if (read_len != -1) {
        for (ssize_t i = 0; i < read_len; i++) {
            if (buffer[i] == '\r' || buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
        }
        
        char* res = remove_parenthesis(buffer);
        if (res != NULL) {
            printf("%s\n", res);
            free(res);
        }
    }
    
    free(buffer);
    return 0;
}