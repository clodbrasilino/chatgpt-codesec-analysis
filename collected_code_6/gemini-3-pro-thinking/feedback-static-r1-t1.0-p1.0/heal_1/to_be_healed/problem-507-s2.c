#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_string_array(char **array, size_t count);
char *duplicate_string(const char *str);
int remove_specific_words(const char *const *input_words, size_t input_count,
                          const char *const *words_to_remove, size_t remove_count,
                          char ***out_words, size_t *out_count);

void free_string_array(char **array, size_t count) {
    if (!array) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

char *duplicate_string(const char *str) {
    if (!str) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *dup = malloc(len + 1);
    if (!dup) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dup, str, len + 1);
    return dup;
}

int remove_specific_words(const char *const *input_words, size_t input_count,
                          const char *const *words_to_remove, size_t remove_count,
                          char ***out_words, size_t *out_count) {
    if (!input_words || !words_to_remove || !out_words || !out_count) {
        return -1;
    }

    *out_words = NULL;
    *out_count = 0;

    if (input_count == 0) {
        return 0;
    }

    char **result = malloc(input_count * sizeof(char *));
    if (!result) {
        return -1;
    }

    size_t current_out_count = 0;

    for (size_t i = 0; i < input_count; i++) {
        if (!input_words[i]) {
            free_string_array(result, current_out_count);
            return -1;
        }

        int should_remove = 0;
        for (size_t j = 0; j < remove_count; j++) {
            if (!words_to_remove[j]) {
                free_string_array(result, current_out_count);
                return -1;
            }
            if (strcmp(input_words[i], words_to_remove[j]) == 0) {
                should_remove = 1;
                break;
            }
        }

        if (!should_remove) {
            char *copied_word = duplicate_string(input_words[i]);
            if (!copied_word) {
                free_string_array(result, current_out_count);
                return -1;
            }
            result[current_out_count] = copied_word;
            current_out_count++;
        }
    }

    if (current_out_count == 0) {
        free(result);
        return 0;
    }

    char **shrunk_result = realloc(result, current_out_count * sizeof(char *));
    if (shrunk_result) {
        result = shrunk_result;
    }

    *out_words = result;
    *out_count = current_out_count;
    
    return 0;
}

int main(void) {
    const char *input[] = {"apple", "banana", "orange", "kiwi", "grape"};
    size_t input_count = sizeof(input) / sizeof(input[0]);

    const char *remove[] = {"banana", "kiwi"};
    size_t remove_count = sizeof(remove) / sizeof(remove[0]);

    char **filtered_words = NULL;
    size_t out_count = 0;

    if (remove_specific_words(input, input_count, remove, remove_count, &filtered_words, &out_count) != 0) {
        fprintf(stderr, "An error occurred during word removal.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_count; i++) {
        printf("%s\n", filtered_words[i]);
    }

    free_string_array(filtered_words, out_count);

    return EXIT_SUCCESS;
}