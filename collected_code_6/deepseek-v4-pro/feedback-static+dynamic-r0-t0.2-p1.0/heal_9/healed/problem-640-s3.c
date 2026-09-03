#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int depth = 0;
    int inside_parenthesis = 0;

    while (i < len) {
        if (str[i] == '(') {
            depth++;
            inside_parenthesis = 1;
            i++;
            continue;
        }
        if (str[i] == ')') {
            if (depth > 0) {
                depth--;
                if (depth == 0) {
                    inside_parenthesis = 0;
                }
            } else {
                result[j++] = str[i];
            }
            i++;
            continue;
        }
        if (!inside_parenthesis && depth == 0) {
            result[j++] = str[i];
        }
        i++;
    }

    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *test1 = "python";
    const char *test2 = "string";
    const char *test3 = "alpha";

    char *r1 = remove_parenthesis_area(test1);
    char *r2 = remove_parenthesis_area(test2);
    char *r3 = remove_parenthesis_area(test3);
    char *r4 = remove_parenthesis_area(NULL);

    printf("Test 1: %s -> %s\n", test1, r1 != NULL ? r1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, r2 != NULL ? r2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, r3 != NULL ? r3 : "NULL");
    printf("Test 4: NULL -> %s\n", r4 != NULL ? r4 : "NULL");

    free(r1);
    free(r2);
    free(r3);
    free(r4);

    return 0;
}