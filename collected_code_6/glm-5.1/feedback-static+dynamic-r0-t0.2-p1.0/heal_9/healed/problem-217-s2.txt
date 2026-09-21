#include <stdio.h>
#include <string.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len < 2) {
        return '\0';
    }

    size_t len = strnlen(str, max_len);
    if (len < 2) {
        return '\0';
    }

    unsigned char char_set[256] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            return (char)c;
        }
        char_set[c] = 1;
    }

    return '\0';
}

int main(void) {
    const char *test_str1 = "programming";
    const char *test_str2 = "abcdef";
    const char *test_str3 = "a";
    const char *test_str4 = NULL;

    char res1 = find_first_repeated(test_str1, strlen(test_str1));
    char res2 = find_first_repeated(test_str2, strlen(test_str2));
    char res3 = find_first_repeated(test_str3, strlen(test_str3));
    char res4 = find_first_repeated(test_str4, 2);

    if (res1 != '\0') {
        printf("First repeated character in '%s': %c\n", test_str1, res1);
    } else {
        printf("No repeated character found in '%s'\n", test_str1);
    }

    if (res2 != '\0') {
        printf("First repeated character in '%s': %c\n", test_str2, res2);
    } else {
        printf("No repeated character found in '%s'\n", test_str2);
    }

    if (res3 != '\0') {
        printf("First repeated character in '%s': %c\n", test_str3, res3);
    } else {
        printf("No repeated character found in '%s'\n", test_str3);
    }

    if (res4 != '\0') {
        printf("First repeated character: %c\n", res4);
    } else {
        printf("No repeated character found in 'NULL'\n");
    }

    return 0;
}