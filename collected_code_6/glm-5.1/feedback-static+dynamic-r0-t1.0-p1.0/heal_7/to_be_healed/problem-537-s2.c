#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 256

char *find_first_repeated_word(const char *str) {
    if (!str) {
        return NULL;
    }

    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (!words) {
        return NULL;
    }

    size_t word_count = 0;
    char *input = strdup(str);
    if (!input) {
        free(words);
        return NULL;
    }

    char *rest = NULL;
    char *token = strtok_r(input, " ,.;:!?()-\t\n\r", &rest);
    while (token != NULL && word_count < MAX_WORDS) {
        for (int i = 0; token[i]; i++) {
            token[i] = tolower((unsigned char)token[i]);
        }
        
        for (size_t i = 0; i < word_count; i++) {
            if (words[i] && strcmp(words[i], token) == 0) {
                char *result = strdup(token);
                free(input);
                for (size_t j = 0; j < word_count; j++) {
                    free(words[j]);
                }
                free(words);
                return result;
            }
        }

        words[word_count] = strdup(token);
        if (!words[word_count]) {
            free(input);
            for (size_t j = 0; j < word_count; j++) {
                free(words[j]);
            }
            free(words);
            return NULL;
        }
        word_count++;
        token = strtok_r(NULL, " ,.;:!?()-\t\n\r", &rest);
    }

    free(input);
    for (size_t j = 0; j < word_count; j++) {
        free(words[j]);
    }
    free(words);
    
    if (word_count > 0) {
        return strdup("None");
    }
    
    return NULL;
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello again.";
    char *repeated = find_first_repeated_word(text);
    
    if (repeated) {
        printf("%s\n", repeated);
        free(repeated);
    } else {
        printf("No words found\n");
    }
    
    const char *empty_text = "No repetitions here.";
    char *repeated2 = find_first_repeated_word(empty_text);
    if (repeated2) {
        printf("%s\n", repeated2);
        free(repeated2);
    }

    const char *null_str = NULL;
    /* Possible weaknesses found:
     *  Calling function 'find_first_repeated_word' returns 0
     *  Assignment 'repeated3=find_first_repeated_word(null_str)', assigned value is 0
     */
    char *repeated3 = find_first_repeated_word(null_str);
    /* Possible weaknesses found:
     *  Condition 'repeated3' is always false [knownConditionTrueFalse]
     *  Condition 'repeated3' is always false
     */
    if (repeated3) {
        printf("%s\n", repeated3);
        free(repeated3);
    }
    
    return 0;
}