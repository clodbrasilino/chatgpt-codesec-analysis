#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

char *first_repeated_word(const char *str) {
    WordEntry *words;
    int word_count = 0;
    size_t i = 0;
    size_t len;
    char *result = NULL;
    char *current_word = NULL;
    size_t current_len = 0;
    size_t current_capacity = 64;
    
    if (str == NULL) {
        return NULL;
    }
    
    words = (WordEntry *)calloc(MAX_WORDS, sizeof(WordEntry));
    if (words == NULL) {
        return NULL;
    }
    
    current_word = (char *)malloc(current_capacity);
    if (current_word == NULL) {
        free(words);
        return NULL;
    }
    
    len = strnlen(str, MAX_WORD_LEN * MAX_WORDS);
    if (len == 0) {
        free(current_word);
        free(words);
        return NULL;
    }
    
    while (i <= len) {
        if (str[i] != '\0' && isalpha((unsigned char)str[i])) {
            if (current_len + 1 >= current_capacity) {
                char *tmp;
                size_t new_capacity = current_capacity * 2;
                if (new_capacity > MAX_WORD_LEN) {
                    new_capacity = MAX_WORD_LEN;
                }
                if (new_capacity <= current_capacity) {
                    break;
                }
                tmp = (char *)realloc(current_word, new_capacity);
                if (tmp == NULL) {
                    free(current_word);
                    free(words);
                    return NULL;
                }
                current_word = tmp;
                current_capacity = new_capacity;
            }
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = tolower((unsigned char)str[i]);
            }
        } else {
            if (current_len > 0) {
                int j;
                int found = 0;
                if (current_len >= MAX_WORD_LEN) {
                    current_len = MAX_WORD_LEN - 1;
                }
                current_word[current_len] = '\0';
                
                for (j = 0; j < word_count; j++) {
                    if (strncmp(words[j].word, current_word, MAX_WORD_LEN - 1) == 0) {
                        words[j].count++;
                        found = 1;
                        if (words[j].count == 2) {
                            result = strdup(words[j].word);
                            free(current_word);
                            free(words);
                            return result;
                        }
                        break;
                    }
                }
                
                if (!found && word_count < MAX_WORDS) {
                    size_t word_len = current_len;
                    if (word_len >= MAX_WORD_LEN) {
                        word_len = MAX_WORD_LEN - 1;
                    }
                    if (word_len < MAX_WORD_LEN) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(words[word_count].word, current_word, word_len);
                        words[word_count].word[word_len] = '\0';
                    } else {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(words[word_count].word, current_word, MAX_WORD_LEN - 1);
                        words[word_count].word[MAX_WORD_LEN - 1] = '\0';
                    }
                    words[word_count].count = 1;
                    word_count++;
                }
                
                current_len = 0;
            }
        }
        i++;
    }
    
    free(current_word);
    free(words);
    return NULL;
}

int main(void) {
    const char str1[] = "This is a test. This is only a test.";
    const char str2[] = "Hello world, hello everyone.";
    const char str3[] = "No repeated words here.";
    const char str4[] = "The cat and the dog and the bird";
    char *result;
    
    result = first_repeated_word(str1);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    result = first_repeated_word(str2);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    result = first_repeated_word(str3);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    result = first_repeated_word(str4);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    result = first_repeated_word(NULL);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    return 0;
}