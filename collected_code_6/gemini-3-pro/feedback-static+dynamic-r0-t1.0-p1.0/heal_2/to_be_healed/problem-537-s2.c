#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* return_none(void) {
    char* none = (char*)malloc(5);
    if (none) {
        snprintf(none, 5, "None");
    }
    return none;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'None', got <no output>
  *  test case 2 failed: expected 'ca', got <no output>
  *  test case 0 failed: expected 'ab', got <no output>
  */

char* find_first_repeated_word(const char* input_string) {
    if (!input_string) {
        return return_none();
    }

    size_t len = 0;
    while (input_string[len] != '\0') {
        len++;
    }

    char* str_copy = (char*)malloc(len + 1);
    char** words = NULL;
    size_t word_count = 0;
    size_t words_capacity = 10;
    char* result = NULL;

    if (!str_copy) {
        return return_none();
    }

    snprintf(str_copy, len + 1, "%s", input_string);

    for (size_t i = 0; i < len; ++i) {
        str_copy[i] = tolower((unsigned char)str_copy[i]);
    }

    words = (char**)malloc(words_capacity * sizeof(char*));
    if (!words) {
        free(str_copy);
        return return_none();
    }

    char* context = NULL;
    char* token = strtok_r(str_copy, " \t\n\r.,!?;:", &context);

    while (token != NULL) {
        if (word_count >= words_capacity) {
            words_capacity *= 2;
            char** temp = (char**)realloc(words, words_capacity * sizeof(char*));
            if (!temp) {
                free(words);
                free(str_copy);
                return return_none();
            }
            words = temp;
        }
        words[word_count++] = token;

        for (size_t i = 0; i < word_count - 1; ++i) {
            if (strcmp(words[i], token) == 0) {
                size_t token_len = 0;
                while (token[token_len] != '\0') {
                    token_len++;
                }
                
                result = (char*)malloc(token_len + 1);
                if (result) {
                    snprintf(result, token_len + 1, "%s", token);
                }
                free(words);
                free(str_copy);
                return result ? result : return_none();
            }
        }

        token = strtok_r(NULL, " \t\n\r.,!?;:", &context);
    }

    free(words);
    free(str_copy);
    return return_none();
}

int main(void) {
    const char* test_string = "This is a test string to test the function.";
    char* repeated_word = find_first_repeated_word(test_string);

    if (repeated_word) {
        printf("First repeated word: %s\n", repeated_word);
        free(repeated_word);
    } else {
        printf("No repeated word found.\n");
    }

    return 0;
}