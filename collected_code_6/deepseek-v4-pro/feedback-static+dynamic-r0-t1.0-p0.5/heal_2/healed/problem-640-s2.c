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
    const char *test2 = "No parentheses here";
    const char *test3 = "Nested (parentheses (inside) here) test";
    const char *test4 = "Unmatched (parenthesis";
    const char *test5 = "Multiple (first) and (second) areas";
    const char *test6 = "";

    char *r1 = remove_parenthesis_area(test1);
    char *r2 = remove_parenthesis_area(test2);
    char *r3 = remove_parenthesis_area(test3);
    char *r4 = remove_parenthesis_area(test4);
    char *r5 = remove_parenthesis_area(test5);
    char *r6 = remove_parenthesis_area(test6);

    printf("Test 1: %s -> %s\n", test1, r1 ? r1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, r2 ? r2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, r3 ? r3 : "NULL");
    printf("Test 4: %s -> %s\n", test4, r4 ? r4 : "NULL");
    printf("Test 5: %s -> %s\n", test5, r5 ? r5 : "NULL");
    printf("Test 6: %s -> %s\n", test6, r6 ? r6 : "NULL");

    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);
    free(r6);

    return 0;
}