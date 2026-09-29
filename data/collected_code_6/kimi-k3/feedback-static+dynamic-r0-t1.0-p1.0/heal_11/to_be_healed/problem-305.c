#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

bool match_words_starting_with_p(const char words[][MAX_WORD_LEN], int count, 
                                char *first_match, char *second_match, size_t buffer_size) {
    if (words == NULL || first_match == NULL || second_match == NULL || 
        buffer_size == 0 || count < 2 || count > MAX_WORDS) {
        return false;
    }
    
    if (buffer_size > MAX_WORD_LEN) {
        return false;
    }
    
    int found = 0;
    
    for (int i = 0; i < count && found < 2; i++) {
        if (words[i][0] == 'p') {
            size_t len = strnlen(words[i], MAX_WORD_LEN);
            if (len >= buffer_size || len >= MAX_WORD_LEN) {
                return false;
            }
            
            if (found == 0) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(first_match, words[i], buffer_size - 1);
                first_match[buffer_size - 1] = '\0';
                found++;
            } else {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(second_match, words[i], buffer_size - 1);
                second_match[buffer_size - 1] = '\0';
                found++;
            }
        }
    }
    
    return (found == 2);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word_list[MAX_WORDS][MAX_WORD_LEN] = {
        "apple", "pear", "peach", "banana", 
        "plum", "orange", "pineapple", "grape"
    };
    int word_count = 8;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first_word[MAX_WORD_LEN] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second_word[MAX_WORD_LEN] = {0};
    
    if (match_words_starting_with_p(word_list, word_count, 
                                   first_word, second_word, MAX_WORD_LEN)) {
        printf("First match: %s\n", first_word);
        printf("Second match: %s\n", second_word);
    } else {
        printf("Could not find two words starting with 'p'\n");
    }
    
    return 0;
}