#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

int find_words_ae(const char *str, char words[][MAX_WORD_LEN]) {
    if (str == NULL || words == NULL) {
        return -1;
    }
    
    int word_count = 0;
    size_t len = strnlen(str, 10000);
    int in_word = 0;
    size_t word_start = 0;
    size_t word_len = 0;
    
    for (size_t i = 0; i <= len; i++) {
        if (i < len && isalnum((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                word_start = i;
                word_len = 0;
            }
            word_len++;
        } else {
            if (in_word) {
                if (word_len > 0 && word_len < MAX_WORD_LEN) {
                    /* Possible weaknesses found:
                     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                     */
                    char current_word[MAX_WORD_LEN];
                    size_t copy_len = word_len < MAX_WORD_LEN - 1 ? word_len : MAX_WORD_LEN - 1;
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(current_word, str + word_start, copy_len);
                    current_word[copy_len] = '\0';
                    
                    char first_char = tolower((unsigned char)current_word[0]);
                    if (first_char == 'a' || first_char == 'e') {
                        if (word_count < MAX_WORDS) {
                            /* Possible weaknesses found:
                             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                             */
                            strncpy(words[word_count], current_word, MAX_WORD_LEN - 1);
                            words[word_count][MAX_WORD_LEN - 1] = '\0';
                            word_count++;
                        }
                    }
                }
                in_word = 0;
            }
        }
    }
    
    return word_count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1000];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }
    
    int count = find_words_ae(input, words);
    
    if (count < 0) {
        printf("Error processing input\n");
        return 1;
    }
    
    printf("Words starting with 'a' or 'e':\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    
    return 0;
}