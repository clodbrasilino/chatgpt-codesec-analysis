#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got  ��
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 1 failed: expected 'string', got `��
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
    const char* str1 = "python( snakes)";
    char* res1 = remove_parenthesis(str1);
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    const char* str2 = "string( cheese)";
    char* res2 = remove_parenthesis(str2);
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    const char* str3 = "alpha( particle)";
    char* res3 = remove_parenthesis(str3);
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    return 0;
}