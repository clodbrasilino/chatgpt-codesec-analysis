#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got @d
  *  test case 2 failed: expected 'alpha', got �d
  *  test case 0 failed: expected 'python', got 
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'len<1024*1024' is not redundant
     *  Either the condition 'len<1024*1024' is redundant or the array 'str[39]' is accessed at index 1048575, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     */
    while (len < 1024 * 1024 && str[len] != '\0') {
        len++;
    }
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'len<1024*1024' is redundant or the array 'str[39]' is accessed at index 1048576, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    if (str[len] != '\0') {
        return NULL;
    }

    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
        }
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
        "string"
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

    const char *input = "Hello (World) C (Programming) Language";
    char *output = remove_parenthesis(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}