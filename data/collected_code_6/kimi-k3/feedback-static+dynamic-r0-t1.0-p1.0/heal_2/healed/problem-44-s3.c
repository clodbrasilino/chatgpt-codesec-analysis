#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_at_start(const char *str, const char *word, size_t word_max_len)
{
    size_t word_len;

    if (str == NULL || word == NULL)
    {
        return false;
    }

    word_len = strnlen(word, word_max_len);

    if (word_len == 0 || word_len == word_max_len)
    {
        return false;
    }

    if (strncmp(str, word, word_len) != 0)
    {
        return false;
    }

    if (str[word_len] != '\0' && !isspace((unsigned char)str[word_len]) && 
        str[word_len] != ',' && str[word_len] != '.' && str[word_len] != '!' && 
        str[word_len] != '?' && str[word_len] != ';' && str[word_len] != ':')
    {
        return false;
    }

    return true;
}

int main(void)
{
    const char *test_str1 = "hello world";
    const char *test_str2 = "hello, world";
    const char *test_str3 = "helloworld";
    const char *test_str4 = "hi there";
    const char *word = "hello";
    const size_t max_word_len = 256;

    printf("Test 1: %s\n", match_word_at_start(test_str1, word, max_word_len) ? "Match" : "No match");
    printf("Test 2: %s\n", match_word_at_start(test_str2, word, max_word_len) ? "Match" : "No match");
    printf("Test 3: %s\n", match_word_at_start(test_str3, word, max_word_len) ? "Match" : "No match");
    printf("Test 4: %s\n", match_word_at_start(test_str4, word, max_word_len) ? "Match" : "No match");
    printf("Test 5: %s\n", match_word_at_start(NULL, word, max_word_len) ? "Match" : "No match");
    printf("Test 6: %s\n", match_word_at_start(test_str1, NULL, max_word_len) ? "Match" : "No match");

    return 0;
}