#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* find_first_repeated_word(const char* input_string) {
    if (input_string == NULL) {
        return NULL;
    }

    char* str_copy = strdup(input_string);
    if (str_copy == NULL) {
        return NULL;
    }

    for (int i = 0; str_copy[i]; i++) {
        str_copy[i] = tolower((unsigned char)str_copy[i]);
    }

    size_t capacity = 10;
    size_t count = 0;
    char** words = malloc(capacity * sizeof(char*));
    if (words == NULL) {
        free(str_copy);
        return NULL;
    }

    char* result = NULL;
    char* saveptr;
    char* token = strtok_r(str_copy, " \t\n\r.,!?;:", &saveptr);

    while (token != NULL) {
        for (size_t i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                result = strdup(token);
                goto cleanup;
            }
        }

        if (count >= capacity) {
            capacity *= 2;
            char** new_words = realloc(words, capacity * sizeof(char*));
            if (new_words == NULL) {
                goto cleanup;
            }
            words = new_words;
        }

        words[count++] = token;
        token = strtok_r(NULL, " \t\n\r.,!?;:", &saveptr);
    }

cleanup:
    free(words);
    free(str_copy);
    return result;
}

int main(void) {
    const char* text = "This is a test. Is it working?";
    char* repeated_word = find_first_repeated_word(text);

    if (repeated_word != NULL) {
        printf("First repeated word: %s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}