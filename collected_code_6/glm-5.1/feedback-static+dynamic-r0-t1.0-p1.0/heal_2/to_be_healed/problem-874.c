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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s, %s: %d\n", test_str1, test_sub1, is_concatenation(test_str1, strlen(test_str1), test_sub1, strlen(test_sub1)));

    const char *test_str2 = "abcab";
    const char *test_sub2 = "abc";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s, %s: %d\n", test_str2, test_sub2, is_concatenation(test_str2, strlen(test_str2), test_sub2, strlen(test_sub2)));

    const char *test_str3 = "aaaa";
    const char *test_sub3 = "a";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s, %s: %d\n", test_str3, test_sub3, is_concatenation(test_str3, strlen(test_str3), test_sub3, strlen(test_sub3)));

    const char *test_str4 = "";
    const char *test_sub4 = "a";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s, %s: %d\n", test_str4, test_sub4, is_concatenation(test_str4, strlen(test_str4), test_sub4, strlen(test_sub4)));

    const char *test_str5 = "abc";
    const char *test_sub5 = "";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%s, %s: %d\n", test_str5, test_sub5, is_concatenation(test_str5, strlen(test_str5), test_sub5, strlen(test_sub5)));

    return 0;
}