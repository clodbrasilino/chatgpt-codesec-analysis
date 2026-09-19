#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_first_repeated(const char *str, char *out) {
    if (str == NULL || out == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    char *count = (char *)calloc(256, sizeof(char));
    if (count == NULL) {
        return -2;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            *out = str[i];
            free(count);
            return 1;
        }
        count[c]++;
    }

    free(count);
    return 0;
}

int main(void) {
    const char *test1 = "abcdefa";
    const char *test2 = "abcdef";
    const char *test3 = "";
    const char *test4 = NULL;

    char res;
    int ret;

    ret = find_first_repeated(test1, &res);
    if (ret == 1) {
        printf("Test 1: %c\n", res);
    } else if (ret == 0) {
        printf("Test 1: No repeated character\n");
    } else {
        printf("Test 1: Error\n");
    }

    ret = find_first_repeated(test2, &res);
    if (ret == 1) {
        printf("Test 2: %c\n", res);
    } else if (ret == 0) {
        printf("Test 2: No repeated character\n");
    } else {
        printf("Test 2: Error\n");
    }

    ret = find_first_repeated(test3, &res);
    if (ret == 1) {
        printf("Test 3: %c\n", res);
    } else if (ret == 0) {
        printf("Test 3: No repeated character\n");
    } else {
        printf("Test 3: Error\n");
    }

    if (test4 != NULL) {
        ret = find_first_repeated(test4, &res);
        if (ret == 1) {
            printf("Test 4: %c\n", res);
        } else if (ret == 0) {
            printf("Test 4: No repeated character\n");
        } else {
            printf("Test 4: Error\n");
        }
    } else {
        printf("Test 4: Error\n");
    }

    return 0;
}