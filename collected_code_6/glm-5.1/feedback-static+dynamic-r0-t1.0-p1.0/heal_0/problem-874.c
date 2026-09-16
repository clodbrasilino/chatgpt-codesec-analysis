#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);

    if (sub_len == 0) {
        return str_len == 0;
    }

    if (str_len == 0 || str_len % sub_len != 0) {
        return false;
    }

    size_t repetitions = str_len / sub_len;

    for (size_t i = 0; i < repetitions; i++) {
        if (strncmp(str + (i * sub_len), sub, sub_len) != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test_str1 = "abcabc";
    const char *test_sub1 = "abc";
    printf("%s, %s: %d\n", test_str1, test_sub1, is_concatenation(test_str1, test_sub1));

    const char *test_str2 = "abcab";
    const char *test_sub2 = "abc";
    printf("%s, %s: %d\n", test_str2, test_sub2, is_concatenation(test_str2, test_sub2));

    const char *test_str3 = "aaaa";
    const char *test_sub3 = "a";
    printf("%s, %s: %d\n", test_str3, test_sub3, is_concatenation(test_str3, test_sub3));

    const char *test_str4 = "";
    const char *test_sub4 = "a";
    printf("%s, %s: %d\n", test_str4, test_sub4, is_concatenation(test_str4, test_sub4));

    const char *test_str5 = "abc";
    const char *test_sub5 = "";
    printf("%s, %s: %d\n", test_str5, test_sub5, is_concatenation(test_str5, test_sub5));

    return 0;
}