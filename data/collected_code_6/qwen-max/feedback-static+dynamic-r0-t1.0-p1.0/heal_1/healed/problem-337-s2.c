#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int ends_with_word(const char *str, const char *word) {
    if (str == NULL || word == NULL || !*str || !*word) return 0;
    size_t len_str = strlen(str);
    size_t len_word = strlen(word);

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