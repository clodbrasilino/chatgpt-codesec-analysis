#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_null_terminated(const char *str, size_t max_len) {
    for (size_t i = 0; i < max_len; ++i) {
        if (str[i] == '\0') return true;
    }
    return false;
}

int ends_with_word(const char *str, const char *word) {
    if (str == NULL || word == NULL || !*str || !*word) return 0;

    size_t len_str = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'len_str<1024' is redundant or the array 'str[12]' is accessed at index 1023, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'len_str<1024' is not redundant
     */
    while (len_str < 1024 && str[len_str] != '\0') len_str++;
    if (!is_null_terminated(str, len_str)) return 0;

    size_t len_word = 0;
    while (len_word < 1024 && word[len_word] != '\0') len_word++;
    if (!is_null_terminated(word, len_word)) return 0;

    if (len_str < len_word) return 0;

    size_t idx_str = len_str - 1;
    while (idx_str > 0 && (ispunct(str[idx_str]) || str[idx_str] == ' ')) --idx_str;

    if (idx_str + 1 < len_word) return 0;

    return strncmp(&str[idx_str + 1 - len_word], word, len_word) == 0;
}

int main() {
    const char *test_str1 = "Hello world.";
    const char *test_str2 = "Hello world";
    const char *test_str3 = "Hello, world!";
    const char *test_str4 = "world is great";
    const char *test_word = "world";

    printf("Test 1: %s\n", ends_with_word(test_str1, test_word) ? "Match" : "No Match");
    printf("Test 2: %s\n", ends_with_word(test_str2, test_word) ? "Match" : "No Match");
    printf("Test 3: %s\n", ends_with_word(test_str3, test_word) ? "Match" : "No Match");
    printf("Test 4: %s\n", ends_with_word(test_str4, test_word) ? "Match" : "No Match");

    return 0;
}