#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got 
  *  test case 0 failed: expected 'python', got �
  *  test case 2 failed: expected 'alpha', got @
  */

char* remove_parenthesis(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    size_t buffer_size = 4096;
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return 1;
    }

    if (fgets(buffer, buffer_size, stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
        
        char* res = remove_parenthesis(buffer);
        if (res != NULL) {
            printf("%s", res);
            free(res);
        }
    }
    
    free(buffer);
    return 0;
}