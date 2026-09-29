#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return '\0';
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        return '\0';
    }

    unsigned char *count = (unsigned char *)calloc(256, sizeof(unsigned char));
    if (count == NULL) {
        return '\0';
    }

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (count[c] > 0) {
            free(count);
            return str[i];
        }
        count[c]++;
    }

    free(count);
    return '\0';
}

int main(void) {
    const char test1[] = "abcdefa";
    const char test2[] = "abcdef";
    const char test3[] = "";
    const char *test4 = NULL;

    char res1 = find_first_repeated(test1, sizeof(test1) - 1);
    char res2 = find_first_repeated(test2, sizeof(test2) - 1);
    char res3 = find_first_repeated(test3, sizeof(test3) - 1);
    char res4 = find_first_repeated(test4, 0);

    if (res1 != '\0') {
        printf("Test 1: %c\n", res1);
    } else {
        printf("Test 1: No repeated character\n");
    }

    if (res2 != '\0') {
        printf("Test 2: %c\n", res2);
    } else {
        printf("Test 2: No repeated character\n");
    }

    if (res3 != '\0') {
        printf("Test 3: %c\n", res3);
    } else {
        printf("Test 3: No repeated character\n");
    }

    if (res4 != '\0') {
        printf("Test 4: %c\n", res4);
    } else {
        printf("Test 4: No repeated character\n");
    }

    return 0;
}