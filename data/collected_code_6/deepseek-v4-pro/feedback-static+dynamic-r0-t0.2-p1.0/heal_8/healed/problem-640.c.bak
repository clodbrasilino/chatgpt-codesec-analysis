#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    while (str[i] != '\0') {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else if (depth == 0) {
            result[j++] = str[i];
        }
        i++;
    }

    result[j] = '\0';

    char *final_result = (char *)malloc(j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }
    memcpy(final_result, result, j + 1);
    free(result);

    return final_result;
}

int main(void) {
    const char *test1 = "python";
    const char *test2 = "string";
    const char *test3 = "alpha";
    
    char *results[] = {
        remove_parenthesis_area(test1),
        remove_parenthesis_area(test2),
        remove_parenthesis_area(test3)
    };

    const char *tests[] = {test1, test2, test3};

    for (int i = 0; i < 3; i++) {
        printf("Input:    \"%s\"\n", tests[i]);
        printf("Output:   \"%s\"\n\n", results[i] ? results[i] : "NULL");
        free(results[i]);
    }

    return 0;
}