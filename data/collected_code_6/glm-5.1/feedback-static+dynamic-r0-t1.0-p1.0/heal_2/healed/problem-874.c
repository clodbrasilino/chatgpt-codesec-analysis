#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_concatenation(const char *str, size_t str_len, const char *sub, size_t sub_len) {
    if (str == NULL || sub == NULL) {
        return false;
    }

    if (sub_len == 0) {
        return str_len == 0;
    }

    if (str_len == 0 || str_len % sub_len != 0) {
        return false;
    }

    size_t repetitions = str_len / sub_len;

    for (size_t i = 0; i < repetitions; i++) {
        if (memcmp(str + (i * sub_len), sub, sub_len) != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test_str1 = "abcabc";
    const char *test_sub1 = "abc";
    size_t len_str1 = strnlen(test_str1, 1024);
    size_t len_sub1 = strnlen(test_sub1, 1024);
    printf("%s, %s: %d\n", test_str1, test_sub1, is_concatenation(test_str1, len_str1, test_sub1, len_sub1));

    const char *test_str2 = "abcab";
    const char *test_sub2 = "abc";
    size_t len_str2 = strnlen(test_str2, 1024);
    size_t len_sub2 = strnlen(test_sub2, 1024);
    printf("%s, %s: %d\n", test_str2, test_sub2, is_concatenation(test_str2, len_str2, test_sub2, len_sub2));

    const char *test_str3 = "aaaa";
    const char *test_sub3 = "a";
    size_t len_str3 = strnlen(test_str3, 1024);
    size_t len_sub3 = strnlen(test_sub3, 1024);
    printf("%s, %s: %d\n", test_str3, test_sub3, is_concatenation(test_str3, len_str3, test_sub3, len_sub3));

    const char *test_str4 = "";
    const char *test_sub4 = "a";
    size_t len_str4 = strnlen(test_str4, 1024);
    size_t len_sub4 = strnlen(test_sub4, 1024);
    printf("%s, %s: %d\n", test_str4, test_sub4, is_concatenation(test_str4, len_str4, test_sub4, len_sub4));

    const char *test_str5 = "abc";
    const char *test_sub5 = "";
    size_t len_str5 = strnlen(test_str5, 1024);
    size_t len_sub5 = strnlen(test_sub5, 1024);
    printf("%s, %s: %d\n", test_str5, test_sub5, is_concatenation(test_str5, len_str5, test_sub5, len_sub5));

    return 0;
}