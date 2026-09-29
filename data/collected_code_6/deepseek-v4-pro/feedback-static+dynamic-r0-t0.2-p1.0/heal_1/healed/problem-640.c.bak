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
            i++;
            continue;
        }
        if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
            i++;
            continue;
        }
        if (depth == 0) {
            result[j++] = str[i];
        }
        i++;
    }

    result[j] = '\0';

    char *final_result = (char *)realloc(result, j + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test1 = "Hello (world) example";
    const char *test2 = "No parentheses here";
    const char *test3 = "Nested (parentheses (inside) here) test";
    const char *test4 = "Unmatched (parenthesis";
    const char *test5 = "Multiple (first) and (second) areas";
    const char *test6 = "";
    const char *test7 = "(only parentheses)";
    const char *test8 = "a(b(c)d)e";

    char *results[] = {
        remove_parenthesis_area(test1),
        remove_parenthesis_area(test2),
        remove_parenthesis_area(test3),
        remove_parenthesis_area(test4),
        remove_parenthesis_area(test5),
        remove_parenthesis_area(test6),
        remove_parenthesis_area(test7),
        remove_parenthesis_area(test8)
    };

    const char *tests[] = {test1, test2, test3, test4, test5, test6, test7, test8};

    for (int i = 0; i < 8; i++) {
        printf("Input:    \"%s\"\n", tests[i]);
        printf("Output:   \"%s\"\n\n", results[i] ? results[i] : "NULL");
        free(results[i]);
    }

    return 0;
}