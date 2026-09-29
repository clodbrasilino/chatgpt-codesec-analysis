#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_at_start(const char *str, size_t str_len, const char *word, size_t word_len)
{
    if (str == NULL || word == NULL)
    {
        return false;
    }

    if (word_len == 0)
    {
        return false;
    }

    if (str_len < word_len)
    {
        return false;
    }

    if (strncmp(str, word, word_len) != 0)
    {
        return false;
    }

    if (word_len < str_len && str[word_len] != '\0' && !isspace((unsigned char)str[word_len]) && 
        str[word_len] != ',' && str[word_len] != '.' && str[word_len] != '!' && 
        str[word_len] != '?' && str[word_len] != ';' && str[word_len] != ':')
    {
        return false;
    }

    return true;
}

size_t safe_strlen(const char *str, size_t max_len)
{
    size_t len = 0;
    if (str == NULL)
    {
        return 0;
    }
    while (len < max_len && str[len] != '\0')
    {
        len++;
    }
    return len;
}

int main(void)
{
    const char *test_str1 = "hello world";
    const char *test_str2 = "hello, world";
    const char *test_str3 = "helloworld";
    const char *test_str4 = "hi there";
    const char *word = "hello";
    const size_t max_len = 256;

    printf("Test 1: %s\n", match_word_at_start(test_str1, safe_strlen(test_str1, max_len), word, safe_strlen(word, max_len)) ? "Match" : "No match");
    printf("Test 2: %s\n", match_word_at_start(test_str2, safe_strlen(test_str2, max_len), word, safe_strlen(word, max_len)) ? "Match" : "No match");
    printf("Test 3: %s\n", match_word_at_start(test_str3, safe_strlen(test_str3, max_len), word, safe_strlen(word, max_len)) ? "Match" : "No match");
    printf("Test 4: %s\n", match_word_at_start(test_str4, safe_strlen(test_str4, max_len), word, safe_strlen(word, max_len)) ? "Match" : "No match");
    printf("Test 5: %s\n", match_word_at_start(NULL, 0, word, safe_strlen(word, max_len)) ? "Match" : "No match");
    printf("Test 6: %s\n", match_word_at_start(test_str1, safe_strlen(test_str1, max_len), NULL, 0) ? "Match" : "No match");

    return 0;
}