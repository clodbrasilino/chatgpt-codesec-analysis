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
    /* Possible weaknesses found:
     *  Variable 'index' is assigned a value that is never used. [unreadVariable]
     */
    int index = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int in_word = 0;
    int word_start = 0;
    int word_len = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
    
    for (int i = 0; i <= len; i++) {
        /* Possible weaknesses found:
         *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
         */
        if (isalnum((unsigned char)str[i]) && i < len) {
            if (!in_word) {
                in_word = 1;
                word_start = i;
                word_len = 0;
            }
            word_len++;
        } else {
            if (in_word) {
                if (word_len < MAX_WORD_LEN) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(current_word, str + word_start, word_len);
                    current_word[word_len] = '\0';
                    
                    if (tolower((unsigned char)current_word[0]) == 'a' || 
                        tolower((unsigned char)current_word[0]) == 'e') {
                        if (word_count < MAX_WORDS) {
                            /* Possible weaknesses found:
                             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                             */
                            strcpy(words[word_count], current_word);
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
    
    input[strcspn(input, "\n")] = '\0';
    
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