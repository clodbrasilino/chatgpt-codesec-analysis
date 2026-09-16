#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis(const char *str) {
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int depth = 0;
    int space_flag = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
                space_flag = 1;
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

    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "python (is great)",
        "(this is a) string",
        "alpha (beta gamma) delta"
    };

    for (int i = 0; i < 3; i++) {
        char *output = remove_parenthesis(test_cases[i]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        printf("%s\n", output);
        free(output);
    }

    return 0;
}