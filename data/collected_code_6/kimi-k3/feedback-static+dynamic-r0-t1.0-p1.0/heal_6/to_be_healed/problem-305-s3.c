#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 64

bool match_two_words_starting_with_p(const char words[][MAX_WORD_LEN], size_t count, char *first_match, char *second_match, size_t buffer_size)
{
    if (words == NULL || first_match == NULL || second_match == NULL || buffer_size == 0)
    {
        return false;
    }

    if (count > MAX_WORDS)
    {
        count = MAX_WORDS;
    }

    size_t found = 0;
    for (size_t i = 0; i < count; i++)
    {
        if (words[i] != NULL && words[i][0] == 'p')
        {
            size_t word_len = strnlen(words[i], MAX_WORD_LEN);
            
            if (word_len >= buffer_size || word_len + 1 > buffer_size)
            {
                return false;
            }
            
            if (found == 0)
            {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(first_match, words[i], buffer_size - 1);
                first_match[buffer_size - 1] = '\0';
                found++;
            }
            else if (found == 1)
            {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(second_match, words[i], buffer_size - 1);
                second_match[buffer_size - 1] = '\0';
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    char words[][MAX_WORD_LEN] = {
        "apple",
        "pear",
        "peach",
        "banana",
        "plum",
        "orange"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[MAX_WORD_LEN] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[MAX_WORD_LEN] = {0};

    if (match_two_words_starting_with_p(words, word_count, first, second, MAX_WORD_LEN))
    {
        printf("First match: %s\n", first);
        printf("Second match: %s\n", second);
    }
    else
    {
        printf("Could not find two words starting with 'p'\n");
    }

    return 0;
}