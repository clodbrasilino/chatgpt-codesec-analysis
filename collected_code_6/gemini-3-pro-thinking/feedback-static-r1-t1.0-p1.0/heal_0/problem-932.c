#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_duplicate_words(char **word_list, size_t input_count, size_t *output_count) {
    if (!word_list || !output_count) {
        return NULL;
    }

    if (input_count == 0) {
        *output_count = 0;
        return NULL;
    }

    char **result = malloc(input_count * sizeof(char *));
    if (!result) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < input_count; i++) {
        if (!word_list[i]) {
            continue;
        }

        int is_duplicate = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (strcmp(result[j], word_list[i]) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            size_t len = strlen(word_list[i]);
            char *new_word = malloc(len + 1);
            if (!new_word) {
                for (size_t k = 0; k < unique_count; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            strcpy(new_word, word_list[i]);
            result[unique_count++] = new_word;
        }
    }

    *output_count = unique_count;
    return result;
}

int main(void) {
    char *sample_words[] = {
        "apple", "banana", "apple", "orange",
        "banana", "grape", "apple", "mango"
    };
    size_t input_count = sizeof(sample_words) / sizeof(sample_words[0]);
    size_t output_count = 0;

    char **unique_words = remove_duplicate_words(sample_words, input_count, &output_count);

    if (!unique_words && input_count > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < output_count; i++) {
        printf("%s\n", unique_words[i]);
    }

    for (size_t i = 0; i < output_count; i++) {
        free(unique_words[i]);
    }
    free(unique_words);

    return EXIT_SUCCESS;
}