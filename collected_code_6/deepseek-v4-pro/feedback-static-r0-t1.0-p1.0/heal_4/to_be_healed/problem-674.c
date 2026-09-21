#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char words[MAX_WORDS][MAX_WORD_LEN];
    int count;
} WordList;

static int is_duplicate(const WordList *list, const char *word) {
    for (int i = 0; i < list->count; i++) {
        if (strncmp(list->words[i], word, MAX_WORD_LEN - 1) == 0 && 
            list->words[i][MAX_WORD_LEN - 1] == '\0') {
            return 1;
        }
    }
    return 0;
}

static int add_word(WordList *list, const char *word) {
    if (list->count >= MAX_WORDS) {
        return 0;
    }
    
    size_t len = strnlen(word, MAX_WORD_LEN);
    if (len >= MAX_WORD_LEN) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->words[list->count], word, len);
    list->words[list->count][len] = '\0';
    list->count++;
    return 1;
}

static void safe_str_copy(char *dest, const char *src, size_t dest_size, size_t src_len) {
    size_t copy_len = (src_len < dest_size) ? src_len : (dest_size > 0 ? dest_size - 1 : 0);
    if (dest_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, copy_len);
        dest[copy_len] = '\0';
    }
}

void remove_duplicate_words(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }

    WordList seen;
    memset(&seen, 0, sizeof(seen));
    
    size_t str_len = strnlen(str, SIZE_MAX);
    if (str_len == 0 || str_len == SIZE_MAX) {
        return;
    }
    
    char *result = (char *)malloc(str_len + 1);
    if (result == NULL) {
        return;
    }
    result[0] = '\0';

    char *str_copy = (char *)malloc(str_len + 1);
    if (str_copy == NULL) {
        free(result);
        return;
    }
    safe_str_copy(str_copy, str, str_len + 1, str_len);

    char *state = NULL;
    char *token = strtok_r(str_copy, " \t\n\r", &state);
    int first = 1;
    size_t current_len = 0;

    while (token != NULL && current_len < str_len) {
        size_t token_len = strnlen(token, str_len - current_len);
        if (token_len == 0) {
            token = strtok_r(NULL, " \t\n\r", &state);
            continue;
        }
        
        if (!is_duplicate(&seen, token)) {
            add_word(&seen, token);
            
            if (!first) {
                if (current_len + 1 < str_len) {
                    result[current_len] = ' ';
                    current_len++;
                    result[current_len] = '\0';
                }
            }
            
            if (current_len + token_len < str_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + current_len, token, token_len);
                current_len += token_len;
                result[current_len] = '\0';
            }
            first = 0;
        }
        token = strtok_r(NULL, " \t\n\r", &state);
    }

    safe_str_copy(str, result, str_len + 1, current_len);
    free(result);
    free(str_copy);
}

int main(void) {
    char str[] = "hello world hello again world test hello";
    
    printf("Original: %s\n", str);
    remove_duplicate_words(str);
    printf("After removing duplicates: %s\n", str);

    return 0;
}