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

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                if (j > 0 && result[j - 1] == ' ') {
                    continue;
                }
                result[j++] = str[i];
            }
        } else {
            if (depth == 0) {
                if (str[i] == ' ') {
                    if (j > 0 && result[j - 1] != ' ') {
                        result[j++] = str[i];
                    }
                } else {
                    result[j++] = str[i];
                }
            }
        }
    }

    if (j > 0 && result[j - 1] == ' ') {
        j--;
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