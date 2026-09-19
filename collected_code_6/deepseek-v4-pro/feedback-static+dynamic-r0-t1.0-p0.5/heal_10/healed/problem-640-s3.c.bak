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

    return result;
}

int main(void) {
    const char *test1 = "Hello (world) example";
    const char *test2 = "Nested (parenthesis (area)) test";
    const char *test3 = "No parentheses here";
    const char *test4 = "Multiple (first) and (second) areas";
    const char *test5 = "Unclosed (parenthesis";
    const char *test6 = "Extra closing) parenthesis";
    const char *test7 = "";
    const char *test8 = "alpha";
    const char *test9 = "python";
    const char *test10 = "string";

    char *results[10];
    results[0] = remove_parenthesis_area(test1);
    results[1] = remove_parenthesis_area(test2);
    results[2] = remove_parenthesis_area(test3);
    results[3] = remove_parenthesis_area(test4);
    results[4] = remove_parenthesis_area(test5);
    results[5] = remove_parenthesis_area(test6);
    results[6] = remove_parenthesis_area(test7);
    results[7] = remove_parenthesis_area(test8);
    results[8] = remove_parenthesis_area(test9);
    results[9] = remove_parenthesis_area(test10);

    printf("Test 1: %s -> %s\n", test1, results[0] ? results[0] : "NULL");
    printf("Test 2: %s -> %s\n", test2, results[1] ? results[1] : "NULL");
    printf("Test 3: %s -> %s\n", test3, results[2] ? results[2] : "NULL");
    printf("Test 4: %s -> %s\n", test4, results[3] ? results[3] : "NULL");
    printf("Test 5: %s -> %s\n", test5, results[4] ? results[4] : "NULL");
    printf("Test 6: %s -> %s\n", test6, results[5] ? results[5] : "NULL");
    printf("Test 7: %s -> %s\n", test7, results[6] ? results[6] : "NULL");
    printf("Test 8: %s -> %s\n", test8, results[7] ? results[7] : "NULL");
    printf("Test 9: %s -> %s\n", test9, results[8] ? results[8] : "NULL");
    printf("Test 10: %s -> %s\n", test10, results[9] ? results[9] : "NULL");

    for (int i = 0; i < 10; i++) {
        free(results[i]);
    }

    return 0;
}