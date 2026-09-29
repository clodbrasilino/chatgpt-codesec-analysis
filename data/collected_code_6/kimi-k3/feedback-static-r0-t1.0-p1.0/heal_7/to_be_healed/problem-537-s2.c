#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 1000

typedef struct {
    char **words;
    int count;
    int capacity;
} WordList;

int is_word_char(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

void to_lowercase(char *dest, const char *src, size_t len) {
    size_t i;
    if (dest == NULL || src == NULL) {
        return;
    }
    for (i = 0; i < len; i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

int find_word(const WordList *list, const char *word) {
    int i;
    if (list == NULL || word == NULL) {
        return 0;
    }
    for (i = 0; i < list->count; i++) {
        if (list->words[i] != NULL && strcmp(list->words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int add_word(WordList *list, const char *word) {
    size_t len;
    char *new_word;
    char **temp;
    
    if (list == NULL || word == NULL) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        int new_capacity = (list->capacity == 0) ? 16 : list->capacity * 2;
        if (new_capacity > MAX_WORDS) {
            new_capacity = MAX_WORDS;
        }
        if (list->count >= new_capacity) {
            return -1;
        }
        temp = realloc(list->words, (size_t)new_capacity * sizeof(char *));
        if (temp == NULL) {
            return -1;
        }
        list->words = temp;
        list->capacity = new_capacity;
    }
    
    len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN) {
        return -1;
    }
    
    new_word = malloc(len + 1);
    if (new_word == NULL) {
        return -1;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_word, word, len);
    }
    new_word[len] = '\0';
    
    list->words[list->count] = new_word;
    list->count++;
    return 0;
}

void free_word_list(WordList *list) {
    int i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        free(list->words[i]);
    }
    free(list->words);
    list->words = NULL;
    list->count = 0;
    list->capacity = 0;
}

char* find_first_repeated_word(const char *str) {
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
    int in_word = 0;
    char *ret = NULL;
    
    if (str == NULL) {
        return NULL;
    }
    
    word_list.words = NULL;
    word_list.count = 0;
    word_list.capacity = 0;
    result[0] = '\0';
    
    while (str[i] != '\0') {
        if (is_word_char(str[i])) {
            if (word_len < MAX_WORD_LEN - 1) {
                current_word[word_len++] = str[i];
            }
            in_word = 1;
        } else {
            if (in_word && word_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 */
                char lower_word[MAX_WORD_LEN];
                /* Possible weaknesses found:
                 *  Either the condition 'copy_len>=100' is redundant or the array 'current_word[100]' is accessed at index 100, which is out of bounds. [arrayIndexOutOfBoundsCond]
                 *  Array index out of bounds
                 */
                current_word[word_len] = '\0';
                to_lowercase(lower_word, current_word, word_len);
                
                if (find_word(&word_list, lower_word)) {
                    /* Possible weaknesses found:
                     *  Assignment to 'copy_len=word_len'
                     */
                    size_t copy_len = word_len;
                    /* Possible weaknesses found:
                     *  Assuming that condition 'copy_len>=100' is not redundant
                     */
                    if (copy_len >= MAX_WORD_LEN) {
                        copy_len = MAX_WORD_LEN - 1;
                    }
                    if (copy_len > 0) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(result, current_word, copy_len);
                    }
                    result[copy_len] = '\0';
                    ret = result;
                    goto cleanup;
                }
                
                if (add_word(&word_list, lower_word) != 0) {
                    ret = NULL;
                    goto cleanup;
                }
                
                word_len = 0;
                in_word = 0;
            }
        }
        i++;
    }
    
    if (in_word && word_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char lower_word[MAX_WORD_LEN];
        /* Possible weaknesses found:
         *  Either the condition 'copy_len>=100' is redundant or the array 'current_word[100]' is accessed at index 100, which is out of bounds. [arrayIndexOutOfBoundsCond]
         *  Array index out of bounds
         */
        current_word[word_len] = '\0';
        to_lowercase(lower_word, current_word, word_len);
        
        if (find_word(&word_list, lower_word)) {
            /* Possible weaknesses found:
             *  Assignment to 'copy_len=word_len'
             */
            size_t copy_len = word_len;
            /* Possible weaknesses found:
             *  Assuming that condition 'copy_len>=100' is not redundant
             */
            if (copy_len >= MAX_WORD_LEN) {
                copy_len = MAX_WORD_LEN - 1;
            }
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result, current_word, copy_len);
            }
            result[copy_len] = '\0';
            ret = result;
            goto cleanup;
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