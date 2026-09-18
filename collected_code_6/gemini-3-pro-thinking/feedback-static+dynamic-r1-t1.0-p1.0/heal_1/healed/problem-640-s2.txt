#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(char *str) {
    if (!str) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;
    int paren_count = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] == '(') {
            paren_count++;
        } else if (str[read_idx] == ')' && paren_count > 0) {
            paren_count--;
        } else if (paren_count == 0) {
            result[write_idx++] = str[read_idx];
        }
        read_idx++;
    }
    
    result[write_idx] = '\0';

    return result;
}

int main(void) {
    char str1[] = "This is a test (to remove).";
    char str2[] = "Nested (parenthesis (are) handled) correctly.";
    char str3[] = "No parentheses here.";
    char str4[] = "Unbalanced (opening parenthesis.";
    char str5[] = "Unbalanced closing) parenthesis.";

    char *res1 = remove_parenthesis_area(str1);
    char *res2 = remove_parenthesis_area(str2);
    char *res3 = remove_parenthesis_area(str3);
    char *res4 = remove_parenthesis_area(str4);
    char *res5 = remove_parenthesis_area(str5);

    if (res1) {
        printf("%s\n", res1);
        free(res1);
    }
    if (res2) {
        printf("%s\n", res2);
        free(res2);
    }
    if (res3) {
        printf("%s\n", res3);
        free(res3);
    }
    if (res4) {
        printf("%s\n", res4);
        free(res4);
    }
    if (res5) {
        printf("%s\n", res5);
        free(res5);
    }

    char *res_null = remove_parenthesis_area(NULL);
    if (res_null) {
        free(res_null);
    }

    return 0;
}