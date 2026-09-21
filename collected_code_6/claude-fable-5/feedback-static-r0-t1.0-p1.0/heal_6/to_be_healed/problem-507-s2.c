#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t bounded_strlen(const char *src, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && src[len] != '\0') {
        len++;
    }
    return len;
}

size_t remove_words(char **list, size_t count, const char **words_to_remove, size_t remove_count)
{
    size_t write_index = 0;
    size_t i;
    size_t j;

    if (list == NULL || words_to_remove == NULL) {
        return count;
    }

    for (i = 0; i < count; i++) {
        int match = 0;

        if (list[i] != NULL) {
            for (j = 0; j < remove_count; j++) {
                if (words_to_remove[j] != NULL &&
                    strcmp(list[i], words_to_remove[j]) == 0) {
                    match = 1;
                    break;
                }
            }
        }

        if (match) {
            free(list[i]);
            list[i] = NULL;
        } else {
            list[write_index] = list[i];
            if (write_index != i) {
                list[i] = NULL;
            }
            write_index++;
        }
    }

    return write_index;
}

char *duplicate_string(const char *src, size_t max_len)
{
    size_t len;
    char *copy;

    if (src == NULL || max_len == 0 || max_len == (size_t)-1) {
        return NULL;
    }

    len = bounded_strlen(src, max_len);

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, src, len);
    }
    copy[len] = '\0';

    return copy;
}

void free_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(list[i]);
        list[i] = NULL;
    }
    free(list);
}

int main(void)
{
    const char *initial_words[] = { "apple", "banana", "cherry", "date", "banana", "fig" };
    const char *words_to_remove[] = { "banana", "date" };
    size_t initial_count = sizeof(initial_words) / sizeof(initial_words[0]);
    size_t remove_count = sizeof(words_to_remove) / sizeof(words_to_remove[0]);
    char **list;
    size_t i;
    size_t new_count;

    list = calloc(initial_count, sizeof(char *));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < initial_count; i++) {
        list[i] = duplicate_string(initial_words[i], 256);
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(list, i);
            return EXIT_FAILURE;
        }
    }

    printf("Original list:\n");
    for (i = 0; i < initial_count; i++) {
        printf("  %s\n", list[i]);
    }

    new_count = remove_words(list, initial_count, words_to_remove, remove_count);

    printf("List after removal:\n");
    for (i = 0; i < new_count; i++) {
        if (list[i] != NULL) {
            printf("  %s\n", list[i]);
        }
    }

    free_list(list, initial_count);

    return EXIT_SUCCESS;
}