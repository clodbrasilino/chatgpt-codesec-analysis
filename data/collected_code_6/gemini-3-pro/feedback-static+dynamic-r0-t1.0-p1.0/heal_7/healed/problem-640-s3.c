#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_parenthesis(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int depth = 0;

    while (input[i] != '\0') {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j++] = input[i];
        }
        i++;
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    char buffer[4096];
    
    if (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
        
        char* res = remove_parenthesis(buffer);
        if (res != NULL) {
            printf("%s\n", res);
            free(res);
        }
    }
    
    return 0;
}