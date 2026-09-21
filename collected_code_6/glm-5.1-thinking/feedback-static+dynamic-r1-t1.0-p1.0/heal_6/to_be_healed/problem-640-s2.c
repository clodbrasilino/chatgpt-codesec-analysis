#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got `#
  *  test case 2 failed: expected 'alpha', got �#
  *  test case 0 failed: expected 'python', got  #
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    int depth = 0;

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else {
            if (depth == 0) {
                len++;
            }
        }
    }

    char *result = calloc(len + 1, sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t write_idx = 0;
    depth = 0;

    for (size_t read_idx = 0; str[read_idx] != '\0'; ++read_idx) {
        if (str[read_idx] == '(') {
            depth++;
        } else if (str[read_idx] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else {
            if (depth == 0) {
                result[write_idx++] = str[read_idx];
            }
        }
    }

    result[write_idx] = '\0';

    return result;
}

int main(void) {
    const char *str1 = "Hello (World)!";
    const char *str2 = "(Nested (Parentheses)) Example";
    const char *str3 = "Unbalanced ( Open";
    const char *str4 = "Unbalanced ) Close";

    char *res1 = remove_parenthesis(str1);
    char *res2 = remove_parenthesis(str2);
    char *res3 = remove_parenthesis(str3);
    char *res4 = remove_parenthesis(str4);

    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }
    if (res4 != NULL) {
        printf("%s\n", res4);
        free(res4);
    }

    return 0;
}