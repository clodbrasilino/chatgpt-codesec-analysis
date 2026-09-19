#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_at_start(const char *str, const char *word)
{
    size_t word_len;
    /* Possible weaknesses found:
     *  Unused variable: i [unusedVariable]
     */
    size_t i;

    if (str == NULL || word == NULL)
    {
        return false;
    }

    word_len = strlen(word);

    if (word_len == 0)
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

    printf("Test 1: %s\n", match_word_at_start(test_str1, word) ? "Match" : "No match");
    printf("Test 2: %s\n", match_word_at_start(test_str2, word) ? "Match" : "No match");
    printf("Test 3: %s\n", match_word_at_start(test_str3, word) ? "Match" : "No match");
    printf("Test 4: %s\n", match_word_at_start(test_str4, word) ? "Match" : "No match");
    printf("Test 5: %s\n", match_word_at_start(NULL, word) ? "Match" : "No match");
    printf("Test 6: %s\n", match_word_at_start(test_str1, NULL) ? "Match" : "No match");

    return 0;
}