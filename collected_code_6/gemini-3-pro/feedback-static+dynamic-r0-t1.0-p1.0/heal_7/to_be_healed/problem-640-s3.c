#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got `��
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 1 failed: expected 'string', got ���
  */

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];
    
    if (fgets(buffer, (int)sizeof(buffer), stdin) != NULL) {
        size_t len = 0;
        
        /* Possible weaknesses found:
         *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
         */
        while (buffer[len] != '\0' && len < sizeof(buffer)) {
            len++;
        }
        
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