#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parentheses(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *output = (char *)malloc(len + 1);
    
    if (output == NULL) {
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
            output[j++] = input[i];
        }
    }
    
    output[j] = '\0';

    return output;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *result = remove_parentheses(argv[i]);
            if (result != NULL) {
                printf("%s\n", result);
                free(result);
            } else {
                fprintf(stderr, "Memory allocation failed or invalid input.\n");
                return EXIT_FAILURE;
            }
        }
    } else {
        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t len = strlen(buffer);
            while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
                buffer[len - 1] = '\0';
                len--;
            }
            char *result = remove_parentheses(buffer);
            if (result != NULL) {
                printf("%s\n", result);
                free(result);
            } else {
                fprintf(stderr, "Memory allocation failed or invalid input.\n");
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}