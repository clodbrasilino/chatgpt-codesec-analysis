#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *words[MAX_WORDS];
    size_t count;
} WordList;

static bool is_word_char(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

static void to_lowercase(char *dest, const char *src, size_t len) {
    size_t i;
    size_t copy_len;
    
    if (dest == NULL || src == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'copy_len=(len<100-1)?len:100-1', assigned value is less than 1
     */
    copy_len = (len < MAX_WORD_LEN - 1) ? len : MAX_WORD_LEN - 1;
    
    /* Possible weaknesses found:
     *  Condition 'i<copy_len' is always false
     *  Condition 'i<copy_len' is always false [knownConditionTrueFalse]
     */
    for (i = 0; i < copy_len; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[copy_len] = '\0';
}

static bool find_word(const WordList *list, const char *word) {
    size_t i;
    
    if (list == NULL || word == NULL) {
        return false;
    }
    
    for (i = 0; i < list->count; i++) {
        if (list->words[i] != NULL && strcmp(list->words[i], word) == 0) {
            return true;
        }
    }
    return false;
}

static int add_word(WordList *list, const char *word) {
    size_t len;
    
    if (list == NULL || word == NULL) {
        return -1;
    }
    
    if (list->count >= MAX_WORDS) {
        return -1;
    }
    
    len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN) {
        return -1;
    }
    
    list->words[list->count] = malloc(len + 1);
    if (list->words[list->count] == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->words[list->count], word, len);
    list->words[list->count][len] = '\0';
    list->count++;
    return 0;
}

static void free_word_list(WordList *list) {
    size_t i;
    
    if (list == NULL) {
        return;
    }
    
    for (i = 0; i < list->count; i++) {
        free(list->words[i]);
        list->words[i] = NULL;
    }
    list->count = 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char result[MAX_WORD_LEN];
    WordList word_list;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    size_t i = 0;
    size_t word_len = 0;
    bool in_word = false;
    char *ret = NULL;
    
    if (str == NULL) {
        return NULL;
    }
    
    word_list.count = 0;
    result[0] = '\0';
    current_word[0] = '\0';
    
    while (str[i] != '\0') {
        if (is_word_char(str[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                current_word[word_len++] = str[i];
            }
            in_word = true;
        } else {
            if (in_word && word_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                char lower_word[MAX_WORD_LEN];
                
                current_word[word_len] = '\0';
                to_lowercase(lower_word, current_word, word_len);
                
                if (find_word(&word_list, lower_word)) {
                    size_t copy_len = (word_len < MAX_WORD_LEN - 1) ? word_len : MAX_WORD_LEN - 1;
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result, current_word, copy_len);
                    result[copy_len] = '\0';
                    ret = result;
                    goto cleanup;
                }
                
                if (add_word(&word_list, lower_word) != 0) {
                    ret = NULL;
                    goto cleanup;
                }
                
                word_len = 0;
                in_word = false;
            }
        }
        i++;
    }
    
    if (in_word && word_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char lower_word[MAX_WORD_LEN];
        
        current_word[word_len] = '\0';
        to_lowercase(lower_word, current_word, word_len);
        
        if (find_word(&word_list, lower_word)) {
            size_t copy_len = (word_len < MAX_WORD_LEN - 1) ? word_len : MAX_WORD_LEN - 1;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, current_word, copy_len);
            result[copy_len] = '\0';
            ret = result;
        }
    }
    
cleanup:
    free_word_list(&word_list);
    return ret;
}

int main(void) {
    const char *test_strings[] = {
        "The quick brown fox jumps over the lazy dog",
        "Hello world hello everyone",
        "one two three four five",
        "apple banana apple cherry",
        "This is a test this is only a test"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        char *repeated;
        
        printf("String: \"%s\"\n", test_strings[i]);
        repeated = find_first_repeated_word(test_strings[i]);
        
        if (repeated != NULL && repeated[0] != '\0') {
            printf("First repeated word: \"%s\"\n\n", repeated);
        } else {
            printf("No repeated words found.\n\n");
        }
    }
    
    return 0;
}