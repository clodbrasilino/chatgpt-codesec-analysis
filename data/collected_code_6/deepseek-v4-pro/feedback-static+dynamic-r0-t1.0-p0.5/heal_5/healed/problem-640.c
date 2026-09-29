#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *remove_parenthesis_area(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    
    size_t initial_size = len + 1;
    if (initial_size <= len) {
        return NULL;
    }

    char *result = (char *)malloc(initial_size);
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
    const char *test1 = "string";
    const char *test2 = "python";
    const char *test3 = "alpha";
    const char *test4 = "Unmatched (parenthesis";
    const char *test5 = "Multiple (first) and (second) areas";
    const char *test6 = "";

    char *result1 = remove_parenthesis_area(test1);
    char *result2 = remove_parenthesis_area(test2);
    char *result3 = remove_parenthesis_area(test3);
    char *result4 = remove_parenthesis_area(test4);
    char *result5 = remove_parenthesis_area(test5);
    char *result6 = remove_parenthesis_area(test6);

    printf("Test 1: %s -> %s\n", test1, result1 ? result1 : "NULL");
    printf("Test 2: %s -> %s\n", test2, result2 ? result2 : "NULL");
    printf("Test 3: %s -> %s\n", test3, result3 ? result3 : "NULL");
    printf("Test 4: %s -> %s\n", test4, result4 ? result4 : "NULL");
    printf("Test 5: %s -> %s\n", test5, result5 ? result5 : "NULL");
    printf("Test 6: \"%s\" -> %s\n", test6, result6 ? result6 : "NULL");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    free(result6);

    return 0;
}