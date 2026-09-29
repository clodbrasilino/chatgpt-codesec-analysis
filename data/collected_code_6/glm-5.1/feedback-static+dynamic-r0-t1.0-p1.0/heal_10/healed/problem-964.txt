#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_length_even(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    size_t len = strnlen(str, max_len);
    return (len % 2) == 0;
}

int main(void) {
    const char word1[] = "hello";
    const char word2[] = "world!";
    const char word3[] = "";
    const char *null_str = NULL;

    if (is_length_even(word1, sizeof(word1))) {
        printf("%s has even length\n", word1);
    } else {
        printf("%s has odd length\n", word1);
    }

    if (is_length_even(word2, sizeof(word2))) {
        printf("%s has even length\n", word2);
    } else {
        printf("%s has odd length\n", word2);
    }

    if (is_length_even(word3, sizeof(word3))) {
        printf("Empty string has even length\n");
    } else {
        printf("Empty string has odd length\n");
    }

    if (null_str != NULL) {
        if (is_length_even(null_str, 9)) {
            printf("NULL has even length\n");
        } else {
            printf("NULL has odd length\n");
        }
    } else {
        printf("Cannot evaluate NULL string length\n");
    }

    return 0;
}