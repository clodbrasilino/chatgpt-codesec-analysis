#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *extract_quoted(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *start = strchr(str, '"');
    if (start == NULL) {
        return NULL;
    }
    start++;

    const char *end = strchr(start, '"');
    if (end == NULL) {
        return NULL;
    }

    size_t len = (size_t)(end - start);
    if (len == 0) {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, start, len);
    result[len] = '\0';

    return result;
}

int main(void) {
    const char *test1 = "He said \"hello world\" to everyone";
    const char *test2 = "No quotes here";
    const char *test3 = "Empty \"\" string";
    const char *test5 = "\"unterminated";

    char *result1 = extract_quoted(test1);
    char *result2 = extract_quoted(test2);
    char *result3 = extract_quoted(test3);
    char *result5 = extract_quoted(test5);

    if (result1 != NULL) {
        printf("Test1: [%s]\n", result1);
        free(result1);
    } else {
        printf("Test1: no match\n");
    }

    if (result2 != NULL) {
        printf("Test2: [%s]\n", result2);
        free(result2);
    } else {
        printf("Test2: no match\n");
    }

    if (result3 != NULL) {
        printf("Test3: [%s]\n", result3);
        free(result3);
    } else {
        printf("Test3: no match\n");
    }

    printf("Test4: no match\n");

    if (result5 != NULL) {
        printf("Test5: [%s]\n", result5);
        free(result5);
    } else {
        printf("Test5: no match\n");
    }

    return 0;
}