#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 100000

char* find_first_repeated_word(const char* str) {
    if (str == NULL) {
        return strdup("None");
    }

    size_t len = strnlen(str, MAX_STR_LEN);
    if (len == MAX_STR_LEN && str[MAX_STR_LEN - 1] != '\0') {
        return strdup("None");
    }

    char** words = (char**)malloc((len + 1) * sizeof(char*));
    if (words == NULL) {
        return strdup("None");
    }

    int word_count = 0;
    const char* p = str;
    
    char* buffer = (char*)malloc(len + 1);
    if (buffer == NULL) {
        free(words);
        return strdup("None");
    }

    int buf_idx = 0;
    char* result = NULL;
    size_t chars_processed = 0;

    while (*p != '\0' && chars_processed < len) {
        if (isalpha((unsigned char)*p)) {
            buffer[buf_idx++] = tolower((unsigned char)*p);
        } else if (buf_idx > 0) {
            buffer[buf_idx] = '\0';
            
            for (int i = 0; i < word_count; i++) {
                if (strcmp(words[i], buffer) == 0) {
                    result = strdup(buffer);
                    goto cleanup;
                }
            }

            words[word_count] = strdup(buffer);
            if (words[word_count] == NULL) {
                goto cleanup;
            }
            word_count++;
            
            buf_idx = 0;
        }
        p++;
        chars_processed++;
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], buffer) == 0) {
                result = strdup(buffer);
                goto cleanup;
            }
        }
    }

cleanup:
    free(buffer);
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);

    if (result == NULL) {
        result = strdup("None");
    }

    return result;
}

int main(void) {
    const char* test_str = "This is a test string and this is another test.";
    char* repeated_word = find_first_repeated_word(test_str);

    if (repeated_word != NULL) {
        printf("First repeated word: %s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}