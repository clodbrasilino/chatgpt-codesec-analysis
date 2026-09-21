#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 4096

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
            if (words_to_remove[j] && strncmp(input_list[i], words_to_remove[j], MAX_WORD_LEN) == 0) {
                match_found = 1;
                break;
            }
        }

        if (!match_found) {
            size_t word_len = 0;
            while (word_len < MAX_WORD_LEN && input_list[i][word_len] != '\0') {
                word_len++;
            }

            filtered_list[count] = malloc(word_len + 1);
            if (!filtered_list[count]) {
                free_word_list(filtered_list, count);
                return NULL;
            }

            snprintf(filtered_list[count], word_len + 1, "%.*s", (int)word_len, input_list[i]);
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