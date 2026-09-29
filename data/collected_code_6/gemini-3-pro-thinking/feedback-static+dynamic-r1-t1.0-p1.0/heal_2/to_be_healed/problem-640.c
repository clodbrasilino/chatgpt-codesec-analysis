#include <stdio.h>
#include <stdlib.h>

char *remove_parentheses(const char *input);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got �4\
  *  test case 0 failed: expected 'python', got �4\
  *  test case 2 failed: expected 'alpha', got  5\
  */

char *remove_parentheses(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

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

    char *resized_output = (char *)realloc(output, j + 1);
    if (resized_output != NULL) {
        return resized_output;
    }

    return output;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = 0;
        while (buffer[len] != '\0') {
            if (buffer[len] == '\n' || buffer[len] == '\r') {
                buffer[len] = '\0';
                break;
            }
            len++;
        }

        char *result = remove_parentheses(buffer);

        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Memory allocation failed or invalid input.\n");
        }
    }

    return EXIT_SUCCESS;
}