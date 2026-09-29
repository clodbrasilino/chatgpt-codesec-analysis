#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100
#define MAX_INPUT_LEN 10000

static int is_valid_char(unsigned char c) {
    return isalnum(c);
}

int find_words_ae(const char *str, char words[][MAX_WORD_LEN]) {
    if (str == NULL || words == NULL) {
        return -1;
    }
    
    int word_count = 0;
    size_t len = strnlen(str, MAX_INPUT_LEN);
    int in_word = 0;
    size_t word_start = 0;
    size_t word_len = 0;
    
    for (size_t i = 0; i <= len; i++) {
        if (i < len && is_valid_char((unsigned char)str[i])) {
            if (!in_word) {
                in_word = 1;
                word_start = i;
                word_len = 0;
            }
            word_len++;
        } else {
            if (in_word) {
                if (word_len > 0 && word_count < MAX_WORDS) {
                    size_t copy_len = word_len;
                    if (copy_len >= MAX_WORD_LEN) {
                        copy_len = MAX_WORD_LEN - 1;
                    }
                    
                    size_t available = len - word_start;
                    if (available < copy_len) {
                        copy_len = available;
                    }
                    
                    /* Possible weaknesses found:
                     *  Assuming condition 'word_start+copy_len<=len' is true
                     */
                    if (copy_len > 0 && word_start + copy_len <= len) {
                        if (tolower((unsigned char)str[word_start]) == 'a' || 
                            tolower((unsigned char)str[word_start]) == 'e') {
                            if (copy_len >= MAX_WORD_LEN) {
                                copy_len = MAX_WORD_LEN - 1;
                            }
                            /* Possible weaknesses found:
                             *  Condition 'word_start+copy_len<=len' is always true
                             *  Condition 'word_start+copy_len<=len' is always true [knownConditionTrueFalse]
                             */
                            if (copy_len < MAX_WORD_LEN && word_start + copy_len <= len) {
                                /* Possible weaknesses found:
                                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                                 */
                                memcpy(words[word_count], str + word_start, copy_len);
                                words[word_count][copy_len] = '\0';
                                word_count++;
                            }
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
    char input[1001] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN] = {{0}};
    
    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
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