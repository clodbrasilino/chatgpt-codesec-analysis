#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
            i++;
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
            i++;
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test1 = "Hello (world) example";
    const char *test2 = "No parentheses here";
    const char *test3 = "Nested (parentheses (inside) here) test";
    const char *test4 = "Unmatched (parenthesis";
    const char *test5 = "Multiple (first) and (second) areas";
    const char *test6 = "";
    const char *test7 = NULL;

    char *result1 = remove_parenthesis_area(test1);
    char *result2 = remove_parenthesis_area(test2);
    char *result3 = remove_parenthesis_area(test3);
    char *result4 = remove_parenthesis_area(test4);
    char *result5 = remove_parenthesis_area(test5);
    char *result6 = remove_parenthesis_area(test6);
    char *result7 = remove_parenthesis_area(test7);

    printf("Test 1: %s -> %s\n", test1, result1 ? result1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, result2 ? result2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, result3 ? result3 : "NULL");
    printf("Test 4: %s -> %s\n", test4, result4 ? result4 : "NULL");
    printf("Test 5: %s -> %s\n", test5, result5 ? result5 : "NULL");
    printf("Test 6: \"%s\" -> %s\n", test6, result6 ? result6 : "NULL");
    printf("Test 7: NULL -> %s\n", result7 ? result7 : "NULL");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);
    free(result7);

    return 0;
}