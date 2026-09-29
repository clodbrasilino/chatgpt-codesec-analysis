#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 50

char** split_string(const char* str, int* word_count) {
    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (!words) return NULL;

    *word_count = 0;
    size_t len = strnlen(str, MAX_WORD_LENGTH * MAX_WORDS);
    if (len >= MAX_WORD_LENGTH * MAX_WORDS) {
        free(words);
        return NULL;
    }

    char temp_str[len + 1];
    memcpy(temp_str, str, len);
    temp_str[len] = '\0';

    char* token = strtok(temp_str, " ");
    while (token && *word_count < MAX_WORDS) {
        size_t token_len = strnlen(token, MAX_WORD_LENGTH);
        if (token_len >= MAX_WORD_LENGTH) {
            while (*word_count > 0) free(words[--*word_count]);
            free(words);
            return NULL;
        }

        words[*word_count] = (char*)malloc((token_len + 1) * sizeof(char));
        if (!words[*word_count]) {
            while (*word_count > 0) free(words[--*word_count]);
            free(words);
            return NULL;
        }

        memcpy(words[*word_count], token, token_len);
        words[*word_count][token_len] = '\0';
        (*word_count)++;
        token = strtok(NULL, " ");
    }

    return words;
}

void free_words(char** words, int word_count) {
    for (int i = 0; i < word_count; i++) {
        free(words[i]);
    }
    free(words);
}

char* remove_duplicates(const char* str) {
    int word_count = 0;
    char** words = split_string(str, &word_count);
    if (!words) return NULL;

    int unique_count = 0;
    for (int i = 0; i < word_count; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            words[unique_count++] = words[i];
        } else {
            free(words[i]);
        }
    }

    size_t result_len = 0;
    for (int i = 0; i < unique_count; i++) {
        result_len += strnlen(words[i], MAX_WORD_LENGTH) + 1;
    }
    char* result = (char*)malloc(result_len * sizeof(char));
    if (!result) {
        free_words(words, unique_count);
        return NULL;
    }
    result[0] = '\0';

    for (int i = 0; i < unique_count; i++) {
        strncat(result, words[i], result_len - strlen(result) - 1);
        if (i < unique_count - 1) {
            strncat(result, " ", result_len - strlen(result) - 1);
        }
    }

    free_words(words, unique_count);
    return result;
}

int main() {
    const char* input = "this this is a test test string string";
    char* result = remove_duplicates(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error: Not enough memory\n");
    }
    return 0;
}