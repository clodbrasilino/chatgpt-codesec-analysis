#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define MAX_WORD_LEN 64
#define MAX_WORDS 100

bool match_two_p_words(const char *words[], size_t count, char *first, char *second, size_t buf_size)
{
    size_t i;
    size_t p_count = 0;
    int ret;
    
    if (words == NULL || first == NULL || second == NULL || buf_size == 0 || count > MAX_WORDS) {
        return false;
    }
    
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (buf_size > INT_MAX) {
        return false;
    }
    
    for (i = 0; i < count && p_count < 2; i++) {
        if (words[i] != NULL && words[i][0] == 'p') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(words[i]) >= buf_size) {
                return false;
            }
            
            if (p_count == 0) {
                ret = snprintf(first, buf_size, "%s", words[i]);
                if (ret < 0 || (size_t)ret >= buf_size) {
                    return false;
                }
                p_count++;
            } else {
                ret = snprintf(second, buf_size, "%s", words[i]);
                if (ret < 0 || (size_t)ret >= buf_size) {
                    return false;
                }
                p_count++;
            }
        }
    }
    
    return (p_count == 2);
}

int main(void)
{
    const char *word_list[] = {
        "apple",
        "pear",
        "peach",
        "banana",
        "plum",
        "orange"
    };
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first_match[MAX_WORD_LEN];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second_match[MAX_WORD_LEN];
    size_t word_count = sizeof(word_list) / sizeof(word_list[0]);
    
    if (word_count > MAX_WORDS) {
        fprintf(stderr, "Error: Too many words in list\n");
        return 1;
    }
    
    if (match_two_p_words(word_list, word_count, first_match, second_match, sizeof(first_match))) {
        printf("First match: %s\n", first_match);
        printf("Second match: %s\n", second_match);
    } else {
        printf("Could not find two words starting with 'p'\n");
    }
    
    return 0;
}