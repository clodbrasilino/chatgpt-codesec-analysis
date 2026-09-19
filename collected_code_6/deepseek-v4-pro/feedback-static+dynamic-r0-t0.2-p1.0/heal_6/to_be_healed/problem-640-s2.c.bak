#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 0 failed: expected 'python', got `��
  *  test case 1 failed: expected 'string', got ���
  */

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
    const char *test2 = "Nested (parenthesis (inside) here) test";
    const char *test3 = "No parenthesis here";
    const char *test4 = "Unmatched (parenthesis";
    const char *test5 = "Multiple (first) and (second) areas";

    char *r1 = remove_parenthesis_area(test1);
    char *r2 = remove_parenthesis_area(test2);
    char *r3 = remove_parenthesis_area(test3);
    char *r4 = remove_parenthesis_area(test4);
    char *r5 = remove_parenthesis_area(test5);

    printf("Test 1: %s -> %s\n", test1, r1 ? r1 : "(null)");
    printf("Test 2: %s -> %s\n", test2, r2 ? r2 : "(null)");
    printf("Test 3: %s -> %s\n", test3, r3 ? r3 : "(null)");
    printf("Test 4: %s -> %s\n", test4, r4 ? r4 : "(null)");
    printf("Test 5: %s -> %s\n", test5, r5 ? r5 : "(null)");

    free(r1);
    free(r2);
    free(r3);
    free(r4);
    free(r5);

    return 0;
}