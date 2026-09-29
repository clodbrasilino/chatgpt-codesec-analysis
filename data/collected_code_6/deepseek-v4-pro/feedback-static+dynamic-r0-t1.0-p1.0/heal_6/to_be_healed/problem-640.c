#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got  �
  *  test case 0 failed: expected 'python', got ��
  *  test case 1 failed: expected 'string', got ��
  */

char *remove_parenthesis_area(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *end = str;
    while (*end != '\0') {
        end++;
    }
    size_t len = (size_t)(end - str);

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int depth = 0;

    while (str[i] != '\0') {
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
        } else if (depth == 0) {
            result[j++] = str[i++];
        } else {
            i++;
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char *test1 = "python";
    const char *test2 = "string";
    const char *test3 = "alpha";
    const char *test4 = "Hello (world) example";
    const char *test5 = "No parentheses here";
    const char *test6 = "Nested (paren(thesis) area) test";
    const char *test7 = "((()))";
    const char *test8 = "Before (unclosed";
    const char *test9 = "After ) unmatched";
    const char *test10 = "Multiple (one) and (two) areas";
    const char *test11 = NULL;

    char *r1 = remove_parenthesis_area(test1);
    char *r2 = remove_parenthesis_area(test2);
    char *r3 = remove_parenthesis_area(test3);
    char *r4 = remove_parenthesis_area(test4);
    char *r5 = remove_parenthesis_area(test5);
    char *r6 = remove_parenthesis_area(test6);
    char *r7 = remove_parenthesis_area(test7);
    char *r8 = remove_parenthesis_area(test8);
    char *r9 = remove_parenthesis_area(test9);
    char *r10 = remove_parenthesis_area(test10);
    /* Possible weaknesses found:
     *  Calling function 'remove_parenthesis_area' returns 0
     *  Assignment 'r11=remove_parenthesis_area(test11)', assigned value is 0
     */
    char *r11 = remove_parenthesis_area(test11);

    if (r1) { printf("Test 1: '%s' -> '%s'\n", test1, r1); free(r1); }
    else { printf("Test 1: '%s' -> %s\n", test1, "NULL"); }

    if (r2) { printf("Test 2: '%s' -> '%s'\n", test2, r2); free(r2); }
    else { printf("Test 2: '%s' -> %s\n", test2, "NULL"); }

    if (r3) { printf("Test 3: '%s' -> '%s'\n", test3, r3); free(r3); }
    else { printf("Test 3: '%s' -> %s\n", test3, "NULL"); }

    if (r4) { printf("Test 4: '%s' -> '%s'\n", test4, r4); free(r4); }
    else { printf("Test 4: '%s' -> %s\n", test4, "NULL"); }

    if (r5) { printf("Test 5: '%s' -> '%s'\n", test5, r5); free(r5); }
    else { printf("Test 5: '%s' -> %s\n", test5, "NULL"); }

    if (r6) { printf("Test 6: '%s' -> '%s'\n", test6, r6); free(r6); }
    else { printf("Test 6: '%s' -> %s\n", test6, "NULL"); }

    if (r7) { printf("Test 7: '%s' -> '%s'\n", test7, r7); free(r7); }
    else { printf("Test 7: '%s' -> %s\n", test7, "NULL"); }

    if (r8) { printf("Test 8: '%s' -> '%s'\n", test8, r8); free(r8); }
    else { printf("Test 8: '%s' -> %s\n", test8, "NULL"); }

    if (r9) { printf("Test 9: '%s' -> '%s'\n", test9, r9); free(r9); }
    else { printf("Test 9: '%s' -> %s\n", test9, "NULL"); }

    if (r10) { printf("Test 10: '%s' -> '%s'\n", test10, r10); free(r10); }
    else { printf("Test 10: '%s' -> %s\n", test10, "NULL"); }

    /* Possible weaknesses found:
     *  Condition 'r11' is always false
     *  Condition 'r11' is always false [knownConditionTrueFalse]
     */
    if (r11) { printf("Test 11: NULL -> '%s'\n", r11); free(r11); }
    else { printf("Test 11: NULL -> %s\n", "NULL"); }

    return 0;
}