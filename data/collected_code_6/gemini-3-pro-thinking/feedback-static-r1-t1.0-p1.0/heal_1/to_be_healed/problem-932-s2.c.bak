#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_duplicate_words(const char **words, size_t input_count, size_t *output_count) {
    if (!words || !output_count) {
        return NULL;
    }

    if (input_count == 0) {
        *output_count = 0;
        return NULL;
    }

    char **unique_words = malloc(input_count * sizeof(char *));
    if (!unique_words) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < input_count; ++i) {
        if (!words[i]) {
            continue;
        }

        int is_duplicate = 0;
        for (size_t j = 0; j < count; ++j) {
            if (strcmp(unique_words[j], words[i]) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (!is_duplicate) {
            size_t len = strlen(words[i]);
            unique_words[count] = malloc(len + 1);
            if (!unique_words[count]) {
                for (size_t k = 0; k < count; ++k) {
                    free(unique_words[k]);
                }
                free(unique_words);
                return NULL;
            }
            memcpy(unique_words[count], words[i], len + 1);
            count++;
        }
    }

    if (count == 0) {
        free(unique_words);
        *output_count = 0;
        return NULL;
    }

    char **resized_words = realloc(unique_words, count * sizeof(char *));
    if (!resized_words) {
        resized_words = unique_words;
    }

    *output_count = count;
    return resized_words;
}

void free_words(char **words, size_t count) {
    if (!words) {
        return;
    }
    for (size_t i = 0; i < count; ++i) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    const char *input_list[] = {
        "apple", "banana", "apple", "orange", 
        "banana", "grape", "grape", "apple"
    };
    /* Possible weaknesses found:
     *  Assignment 'input_count=sizeof(input_list)/sizeof(input_list[0])', assigned value is 8
     */
    size_t input_count = sizeof(input_list) / sizeof(input_list[0]);
    size_t output_count = 0;

    char **unique_list = remove_duplicate_words(input_list, input_count, &output_count);

    if (unique_list) {
        for (size_t i = 0; i < output_count; ++i) {
            printf("%s\n", unique_list[i]);
        }
        free_words(unique_list, output_count);
    /* Possible weaknesses found:
     *  Condition 'input_count>0' is always true [knownConditionTrueFalse]
     *  Condition 'input_count>0' is always true
     */
    } else if (input_count > 0) {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}