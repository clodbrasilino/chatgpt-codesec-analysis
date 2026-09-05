#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int word_in_list(const char *word, char **list, size_t count);
size_t remove_words(char **words, size_t count, char **to_remove, size_t remove_count);

int main(void)
{
    const char *initial[] = {"apple", "banana", "cherry", "banana", "date", "fig"};
    char *to_remove[] = {"banana", "date"};
    size_t count = sizeof(initial) / sizeof(initial[0]);
    size_t remove_count = sizeof(to_remove) / sizeof(to_remove[0]);
    char **words = NULL;
    size_t new_count = 0;
    size_t i;
    size_t j;

    words = malloc(count * sizeof(*words));
    if (words == NULL) {
        fprintf(stderr, "Error: failed to allocate word list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        size_t len = strlen(initial[i]) + 1;
        words[i] = malloc(len);
        if (words[i] == NULL) {
            fprintf(stderr, "Error: failed to allocate word\n");
            for (j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return EXIT_FAILURE;
        }
        memcpy(words[i], initial[i], len);
    }

    printf("Original list: ");
    for (i = 0; i < count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    new_count = remove_words(words, count, to_remove, remove_count);

    printf("Filtered list: ");
    for (i = 0; i < new_count; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    for (i = 0; i < new_count; i++) {
        free(words[i]);
    }
    free(words);

    return EXIT_SUCCESS;
}

static int word_in_list(const char *word, char **list, size_t count)
{
    size_t i;

    if (word == NULL || list == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (list[i] != NULL && strcmp(word, list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

size_t remove_words(char **words, size_t count, char **to_remove, size_t remove_count)
{
    size_t i;
    size_t kept = 0;

    if (words == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL && !word_in_list(words[i], to_remove, remove_count)) {
            words[kept] = words[i];
            kept++;
        } else {
            free(words[i]);
        }
    }

    for (i = kept; i < count; i++) {
        words[i] = NULL;
    }

    return kept;
}