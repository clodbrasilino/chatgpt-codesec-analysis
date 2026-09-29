#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_REPEATED_CHAR -1

int find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL) {
        return NO_REPEATED_CHAR;
    }

    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return NO_REPEATED_CHAR;
    }

    char *count = (char *)calloc(256, sizeof(char));
    if (count == NULL) {
        return NO_REPEATED_CHAR;
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            free(count);
            return c;
        }
        count[c]++;
    }

    free(count);
    return NO_REPEATED_CHAR;
}

int main(void) {
    const char *test1 = "abcdefa";
    const char *test2 = "abcdef";
    const char *test3 = "";
    const char *test4 = NULL;

    int res1 = find_first_repeated(test1, 32);
    int res2 = find_first_repeated(test2, 32);
    int res3 = find_first_repeated(test3, 32);
    int res4 = find_first_repeated(test4, 32);

    if (res1 != NO_REPEATED_CHAR) {
        printf("Test 1: %c\n", res1);
    } else {
        printf("Test 1: No repeated character\n");
    }

    if (res2 != NO_REPEATED_CHAR) {
        printf("Test 2: %c\n", res2);
    } else {
        printf("Test 2: No repeated character\n");
    }

    if (res3 != NO_REPEATED_CHAR) {
        printf("Test 3: %c\n", res3);
    } else {
        printf("Test 3: No repeated character\n");
    }

    if (res4 != NO_REPEATED_CHAR) {
        printf("Test 4: %c\n", res4);
    } else {
        printf("Test 4: No repeated character\n");
    }

    return 0;
}