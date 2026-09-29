#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_string_into_characters(const char* str, size_t* count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    *count = len;

    if (len == 0) {
        return NULL;
    }

    char** chars = (char**)malloc(len * sizeof(char*));
    if (chars == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        chars[i] = (char*)malloc(2 * sizeof(char));
        if (chars[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(chars[j]);
            }
            free(chars);
            return NULL;
        }
        chars[i][0] = str[i];
        chars[i][1] = '\0';
    }

    return chars;
}

void free_character_array(char** chars, size_t count) {
    if (chars != NULL) {
        for (size_t i = 0; i < count; i++) {
            free(chars[i]);
        }
        free(chars);
    }
}

int main(void) {
    const char* test_string = "Hello, World!";
    size_t count = 0;
    
    char** characters = split_string_into_characters(test_string, &count);
    
    if (characters != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Character %zu: %s\n", i, characters[i]);
        }
        free_character_array(characters, count);
    } else {
        printf("Failed to split string or string is empty.\n");
    }

    return 0;
}