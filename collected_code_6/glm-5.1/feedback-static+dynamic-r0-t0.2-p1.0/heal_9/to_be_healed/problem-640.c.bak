#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got `��
  *  test case 0 failed: expected 'python', got ��
  *  test case 2 failed: expected 'alpha', got ���
  */

char *remove_parenthesis(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    size_t depth = 0;
    int space_flag = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
            if (j > 0 && depth == 1) {
                space_flag = 1;
            }
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
                if (depth == 0 && space_flag) {
                    result[j++] = ' ';
                    space_flag = 0;
                }
            } else {
                if (space_flag) {
                    result[j++] = ' ';
                    space_flag = 0;
                }
                result[j++] = str[i];
            }
        } else {
            if (depth == 0) {
                if (str[i] == ' ') {
                    if (j > 0) {
                        space_flag = 1;
                    }
                } else {
                    if (space_flag) {
                        result[j++] = ' ';
                        space_flag = 0;
                    }
                    result[j++] = str[i];
                }
            }
        }
    }

    if (space_flag) {
        result[j++] = ' ';
    }
    
    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk) {
        return shrunk;
    }
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "python",
        "alpha",
        "string",
        "Hello (World) C (Programming) Language"
    };
    
    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        char *output = remove_parenthesis(test_cases[i]);
        if (output) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }
    
    return 0;
}