#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got @��
  *  test case 1 failed: expected 'string', got 
  *  test case 0 failed: expected 'python', got ���
  */

char *remove_parenthesis_area(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t result_len = 0;
    int depth = 0;
    const char *p = str;

    while (*p) {
        if (*p == '(') {
            depth++;
        } else if (*p == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result_len++;
            }
        } else if (depth == 0) {
            result_len++;
        }
        p++;
    }

    char *result = (char *)malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    depth = 0;
    p = str;

    while (*p) {
        if (*p == '(') {
            depth++;
        } else if (*p == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = *p;
            }
        } else if (depth == 0) {
            result[j++] = *p;
        }
        p++;
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test1 = "alpha";
    const char *test2 = "python";
    const char *test3 = "string";
    const char *test4 = "Hello (world) example";
    const char *test5 = "Nested (parenthesis (area)) test";
    const char *test6 = "No parentheses here";
    const char *test7 = "Multiple (first) and (second) areas";
    const char *test8 = "Unclosed (parenthesis";
    const char *test9 = "Extra closing) parenthesis";
    const char *test10 = "";

    char *result1 = remove_parenthesis_area(test1);
    char *result2 = remove_parenthesis_area(test2);
    char *result3 = remove_parenthesis_area(test3);
    char *result4 = remove_parenthesis_area(test4);
    char *result5 = remove_parenthesis_area(test5);
    char *result6 = remove_parenthesis_area(test6);
    char *result7 = remove_parenthesis_area(test7);
    char *result8 = remove_parenthesis_area(test8);
    char *result9 = remove_parenthesis_area(test9);
    char *result10 = remove_parenthesis_area(test10);

    printf("Test 1: %s -> %s\n", test1, result1 ? result1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, result2 ? result2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, result3 ? result3 : "NULL");
    printf("Test 4: %s -> %s\n", test4, result4 ? result4 : "NULL");
    printf("Test 5: %s -> %s\n", test5, result5 ? result5 : "NULL");
    printf("Test 6: %s -> %s\n", test6, result6 ? result6 : "NULL");
    printf("Test 7: %s -> %s\n", test7, result7 ? result7 : "NULL");
    printf("Test 8: %s -> %s\n", test8, result8 ? result8 : "NULL");
    printf("Test 9: %s -> %s\n", test9, result9 ? result9 : "NULL");
    printf("Test 10: %s -> %s\n", test10, result10 ? result10 : "NULL");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);
    free(result7);
    free(result8);
    free(result9);
    free(result10);

    return 0;
}