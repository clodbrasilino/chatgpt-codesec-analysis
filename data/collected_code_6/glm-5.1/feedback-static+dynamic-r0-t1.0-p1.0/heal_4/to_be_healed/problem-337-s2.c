#include <stdio.h>
#include <string.h>
#include <ctype.h>

int match_word_at_end(const char *str, size_t str_len, const char *word, size_t word_len) {
    size_t effective_str_len;
    const char *p;

    if (str == NULL || word == NULL || str_len == 0 || word_len == 0) {
        return 0;
    }

    p = str + str_len - 1;

    while (p >= str && ispunct((unsigned char)*p)) {
        p--;
    }

    if (p < str) {
        return 0;
    }

    effective_str_len = (size_t)(p - str + 1);

    if (effective_str_len < word_len) {
        return 0;
    }

    if (effective_str_len > word_len) {
        if (!isspace((unsigned char)str[effective_str_len - word_len - 1])) {
            return 0;
        }
    }

    for (size_t i = 0; i < word_len; i++) {
        if (str[effective_str_len - word_len + i] != word[i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    const char *test_str1 = "Hello world!";
    const char *test_str2 = "Hello world";
    const char *test_str3 = "world";
    const char *test_str4 = "Helloworld";
    const char *test_str5 = "Hello world...";
    const char *test_str6 = "Hello world, how are you?";
    const char *test_word = "world";

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%d\n", match_word_at_end(test_str1, strlen(test_str1), test_word, strlen(test_word)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%d\n", match_word_at_end(test_str2, strlen(test_str2), test_word, strlen(test_word)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%d\n", match_word_at_end(test_str3, strlen(test_str3), test_word, strlen(test_word)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%d\n", match_word_at_end(test_str4, strlen(test_str4), test_word, strlen(test_word)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%d\n", match_word_at_end(test_str5, strlen(test_str5), test_word, strlen(test_word)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("%d\n", match_word_at_end(test_str6, strlen(test_str6), test_word, strlen(test_word)));

    return 0;
}