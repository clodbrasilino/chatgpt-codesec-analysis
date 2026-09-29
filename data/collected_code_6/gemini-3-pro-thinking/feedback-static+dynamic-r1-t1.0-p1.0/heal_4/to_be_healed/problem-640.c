#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got �U
  *  test case 2 failed: expected 'alpha', got �U
  *  test case 0 failed: expected 'python', got @U
  */

char *remove_parentheses(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

int main(void) {
    size_t capacity = 4096;
    char *buffer = (char *)malloc(capacity);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    buffer[0] = '\0';
    size_t len = 0;

    while (fgets(buffer + len, (int)(capacity - len), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        len += strlen(buffer + len);

        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
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
            }
            
            len = 0;
            buffer[0] = '\0';
        } else if (len >= capacity - 1) {
            size_t new_capacity = capacity * 2;
            char *new_buffer = (char *)realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
    }

    if (len > 0) {
        char *result = remove_parentheses(buffer);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed or invalid input.\n");
        }
    }

    free(buffer);
    return EXIT_SUCCESS;
}