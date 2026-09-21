#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **remove_specific_words(const char **input_list, size_t input_size, const char **words_to_remove, size_t remove_size, size_t *output_size);
void free_word_list(char **list, size_t size);

char **remove_specific_words(const char **input_list, size_t input_size, const char **words_to_remove, size_t remove_size, size_t *output_size) {
    if (!input_list || !words_to_remove || !output_size) {
        return NULL;
    }

    char **filtered_list = malloc(input_size * sizeof(char *));
    if (!filtered_list) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input_size; i++) {
        if (!input_list[i]) {
            continue;
        }

        int match_found = 0;
        for (size_t j = 0; j < remove_size; j++) {
            if (words_to_remove[j] && strcmp(input_list[i], words_to_remove[j]) == 0) {
                match_found = 1;
                break;
            }
        }

        if (!match_found) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t word_len = strlen(input_list[i]);
            filtered_list[count] = malloc(word_len + 1);
            if (!filtered_list[count]) {
                free_word_list(filtered_list, count);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(filtered_list[count], input_list[i], word_len + 1);
            count++;
        }
    }

    *output_size = count;

    if (count == 0) {
        free(filtered_list);
        return NULL;
    }

    char **resized_list = realloc(filtered_list, count * sizeof(char *));
    if (resized_list) {
        filtered_list = resized_list;
    }

    return filtered_list;
}

void free_word_list(char **list, size_t size) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *original_list[] = {"apple", "banana", "orange", "kiwi", "grape", "banana"};
    size_t original_size = sizeof(original_list) / sizeof(original_list[0]);

    const char *words_to_remove[] = {"banana", "kiwi"};
    size_t remove_size = sizeof(words_to_remove) / sizeof(words_to_remove[0]);

    size_t new_size = 0;
    char **new_list = remove_specific_words(original_list, original_size, words_to_remove, remove_size, &new_size);

    if (new_list) {
        for (size_t i = 0; i < new_size; i++) {
            printf("%s\n", new_list[i]);
        }
        free_word_list(new_list, new_size);
    }

    return 0;
}