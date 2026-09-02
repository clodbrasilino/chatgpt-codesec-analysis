#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_words_starting_with_p(char *words[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (words[i] != NULL && words[i][0] == 'p') {
            count++;
        }
    }
    return count;
}

char **find_matching_words(char *words[], int size, int *match_count) {
    if (words == NULL || match_count == NULL || size <= 0) {
        if (match_count != NULL) {
            *match_count = 0;
        }
        return NULL;
    }

    int count = count_words_starting_with_p(words, size);
    *match_count = count;

    if (count == 0) {
        return NULL;
    }

    char **matches = (char **)malloc(count * sizeof(char *));
    if (matches == NULL) {
        *match_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        if (words[i] != NULL && words[i][0] == 'p') {
            matches[index++] = words[i];
        }
    }

    return matches;
}

void free_matches(char **matches) {
    if (matches != NULL) {
        free(matches);
    }
}

int main(void) {
    char *word_list[] = {"apple", "pear", "banana", "plum", "peach", "kiwi", "pineapple"};
    int list_size = sizeof(word_list) / sizeof(word_list[0]);
    int match_count = 0;

    char **matches = find_matching_words(word_list, list_size, &match_count);

    if (matches != NULL) {
        for (int i = 0; i < match_count; i++) {
            printf("%s\n", matches[i]);
        }
        free_matches(matches);
    } else if (match_count == 0) {
        printf("No matches found.\n");
    } else {
        printf("Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}