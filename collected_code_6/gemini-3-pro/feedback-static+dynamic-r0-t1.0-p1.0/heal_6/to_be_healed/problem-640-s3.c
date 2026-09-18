#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got 
  *  test case 2 failed: expected 'alpha', got �J
  *  test case 1 failed: expected 'string', got @J
  */

char* remove_parenthesis(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
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
    char buffer[2048];
    while (scanf("%2047s", buffer) == 1) {
        char* res = remove_parenthesis(buffer);
        if (res != NULL) {
            printf("%s\n", res);
            free(res);
        }
    }
    return 0;
}