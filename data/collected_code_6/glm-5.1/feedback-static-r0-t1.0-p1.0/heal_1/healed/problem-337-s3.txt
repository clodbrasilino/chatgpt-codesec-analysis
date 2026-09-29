#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool match_word_at_end(const char *str, const char *word, size_t str_max_len, size_t word_max_len) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t str_len = strnlen(str, str_max_len);
    size_t word_len = strnlen(word, word_max_len);

    if (str_len == 0 || word_len == 0) {
        return false;
    }

    const char *str_ptr = str + str_len - 1;

    while (str_ptr >= str && (*str_ptr == '.' || *str_ptr == ',' || *str_ptr == '!' || *str_ptr == '?' || *str_ptr == ';' || *str_ptr == ':')) {
        if (str_ptr == str) {
            break;
        }
        str_ptr--;
    }

    if (str_ptr < str) {
        return false;
    }

    size_t remaining_len = (str_ptr - str) + 1;

    if (word_len > remaining_len) {
        return false;
    }

    if (word_len < remaining_len) {
        if (*(str_ptr - word_len) != ' ') {
            return false;
        }
    }

    return strncmp(str_ptr - word_len + 1, word, word_len) == 0;
}

int main() {
    const char *test_str1 = "Hello world!";
    const char *test_str2 = "Hello world";
    const char *test_str3 = "Hello worlds";
    const char *test_str4 = "world";
    const char *test_str5 = "world?";
    const char *test_str6 = "Hello world.";
    const char *word = "world";

    printf("%d\n", match_word_at_end(test_str1, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(test_str2, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(test_str3, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(test_str4, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(test_str5, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(test_str6, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(NULL, word, SIZE_MAX, SIZE_MAX));
    printf("%d\n", match_word_at_end(test_str1, NULL, SIZE_MAX, SIZE_MAX));

    return 0;
}