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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got (null)
  */

char *first_repeated_word(const char *str) {
    WordEntry *words;
    int word_count = 0;
    size_t i = 0;
    size_t len;
    char *result = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
                            size_t word_len = strnlen(words[j].word, MAX_WORD_LEN);
                            result = (char *)malloc(word_len + 1);
                            if (result != NULL) {
                                /* Possible weaknesses found:
                                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                                 */
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
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
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
    /* Possible weaknesses found:
     *  Variable 'str1' can be declared as const array [constVariable]
     */
    char str1[] = "This is a test. This is only a test.";
    /* Possible weaknesses found:
     *  Variable 'str2' can be declared as const array [constVariable]
     */
    char str2[] = "Hello world, hello everyone.";
    /* Possible weaknesses found:
     *  Variable 'str3' can be declared as const array [constVariable]
     */
    char str3[] = "No repeated words here.";
    /* Possible weaknesses found:
     *  Variable 'str4' can be declared as const array [constVariable]
     */
    char str4[] = "The cat and the dog and the bird";
    /* Possible weaknesses found:
     *  Variable 'str5' can be declared as const array [constVariable]
     */
    char str5[] = "ab ca bc ab ca";
    /* Possible weaknesses found:
     *  Variable 'str6' can be declared as const array [constVariable]
     */
    char str6[] = "ab ca bc";
    /* Possible weaknesses found:
     *  Variable 'str7' can be declared as const array [constVariable]
     */
    char str7[] = "ca bc ab";
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