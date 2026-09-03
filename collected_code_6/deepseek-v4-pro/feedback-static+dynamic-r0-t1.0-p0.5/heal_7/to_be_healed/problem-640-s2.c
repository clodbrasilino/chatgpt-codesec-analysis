#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got  ��
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 1 failed: expected 'string', got `��
  */

char *remove_parenthesis_area(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int depth = 0;

    while (i < len) {
        if (str[i] == '(') {
            depth++;
            i++;
            continue;
        }
        if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
            i++;
            continue;
        }
        if (depth == 0) {
            result[j++] = str[i];
        }
        i++;
    }

    while (j > 0 && result[j - 1] == ' ') {
        j--;
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *tests[] = {
        "python",
        "string",
        "alpha",
        "Hello (world) example",
        "No parentheses here",
        "Nested (parentheses (inside) here) test",
        "Unmatched (parenthesis",
        "Multiple (first) and (second) areas",
        ""
    };
    
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        char *result = remove_parenthesis_area(tests[i]);
        printf("Test %zu: %s -> %s\n", i, tests[i], result ? result : "NULL");
        free(result);
    }

    return 0;
}