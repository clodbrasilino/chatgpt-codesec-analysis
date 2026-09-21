#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

char *first_repeated_word(const char *str) {
    WordEntry *words;
    int word_count = 0;
    size_t i = 0;
    size_t len;
    char *result = NULL;
    char current_word[MAX_WORD_LEN];
    size_t current_len = 0;
    
    if (str == NULL) {
        return NULL;
    }
    
    len = strnlen(str, MAX_WORD_LEN * MAX_WORDS);
    
    words = (WordEntry *)calloc(MAX_WORDS, sizeof(WordEntry));
    if (words == NULL) {
        return NULL;
    }
    
    while (i <= len) {
        if (i < len && isalpha((unsigned char)str[i])) {
            if (current_len < MAX_WORD_LEN - 1) {
                current_word[current_len++] = (char)tolower((unsigned char)str[i]);
            }
        } else {
            if (current_len > 0) {
                int j;
                int found = 0;
                current_word[current_len] = '\0';
                
                for (j = 0; j < word_count; j++) {
                    if (strcmp(words[j].word, current_word) == 0) {
                        words[j].count++;
                        found = 1;
                        if (words[j].count == 2) {
                            size_t word_len = strnlen(words[j].word, MAX_WORD_LEN - 1);
                            result = (char *)malloc(word_len + 1);
                            if (result != NULL) {
                                memcpy(result, words[j].word, word_len);
                                result[word_len] = '\0';
                            }
                            free(words);
                            return result;
                        }
                        break;
                    }
                }
                
                if (!found && word_count < MAX_WORDS) {
                    size_t copy_len = current_len < MAX_WORD_LEN - 1 ? current_len : MAX_WORD_LEN - 1;
                    memcpy(words[word_count].word, current_word, copy_len);
                    words[word_count].word[copy_len] = '\0';
                    words[word_count].count = 1;
                    word_count++;
                }
                
                current_len = 0;
            }
        }
        i++;
    }
    
    free(words);
    return NULL;
}

int main(void) {
    const char str1[] = "This is a test. This is only a test.";
    const char str2[] = "Hello world, hello everyone.";
    const char str3[] = "No repeated words here.";
    const char str4[] = "The cat and the dog and the bird";
    const char str5[] = "ab ca bc ab ca";
    const char str6[] = "ab ca bc";
    const char str7[] = "ca bc ab";
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
    
    result = first_repeated_word(str5);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    result = first_repeated_word(str6);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    result = first_repeated_word(str7);
    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }
    
    return 0;
}