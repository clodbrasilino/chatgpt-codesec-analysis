#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_into_characters(const char* str, size_t* num_chars) {
    if (str == NULL || num_chars == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    *num_chars = len;

    char** chars_array = (char**)calloc(len, sizeof(char*));
    if (chars_array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        chars_array[i] = (char*)malloc(2 * sizeof(char));
        if (chars_array[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(chars_array[j]);
            }
            free(chars_array);
            return NULL;
        }
        chars_array[i][0] = str[i];
        chars_array[i][1] = '\0';
    }

    return chars_array;
}

void free_character_array(char** chars_array, size_t num_chars) {
    if (chars_array != NULL) {
        for (size_t i = 0; i < num_chars; i++) {
            free(chars_array[i]);
        }
        free(chars_array);
    }
}

int main(void) {
    const char* input_string = "Hello";
    size_t count = 0;

    char** result = split_into_characters(input_string, &count);

    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_character_array(result, count);
    } else {
        fprintf(stderr, "Failed to split string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}