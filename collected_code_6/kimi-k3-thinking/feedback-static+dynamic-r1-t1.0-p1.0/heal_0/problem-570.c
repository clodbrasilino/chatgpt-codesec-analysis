#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_substring(const char *word, const char *substr)
{
    if (word == NULL || substr == NULL) {
        return 0;
    }
    if (substr[0] == '\0') {
        return 0;
    }
    return strstr(word, substr) != NULL;
}

static int remove_words_containing(char **words, size_t count,
                                   const char *substr, size_t *result_count)
{
    size_t read_idx;
    size_t write_idx;

    if (words == NULL || substr == NULL || result_count == NULL) {
        return -1;
    }

    write_idx = 0;
    for (read_idx = 0; read_idx < count; read_idx++) {
        if (words[read_idx] == NULL) {
            continue;
        }
        if (contains_substring(words[read_idx], substr)) {
            free(words[read_idx]);
            words[read_idx] = NULL;
        } else {
            words[write_idx] = words[read_idx];
            if (write_idx != read_idx) {
                words[read_idx] = NULL;
            }
            write_idx++;
        }
    }

    *result_count = write_idx;
    return 0;
}

static void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

static void print_words(const char *label, char *const *words, size_t count)
{
    size_t i;

    printf("%s\n", label);
    for (i = 0; i < count; i++) {
        if (words[i] != NULL) {
            printf("%s\n", words[i]);
        }
    }
}

int main(void)
{
    static const char *initial[] = {
        "apple", "banana", "cherry", "grape", "melon", "apricot"
    };
    const size_t count = sizeof(initial) / sizeof(initial[0]);
    char **words;
    size_t i;
    size_t new_count;

    words = calloc(count, sizeof(*words));
    if (words == NULL) {
        fprintf(stderr, "Failed to allocate word list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        size_t len = strlen(initial[i]) + 1;
        words[i] = malloc(len);
        if (words[i] == NULL) {
            fprintf(stderr, "Failed to allocate word\n");
            free_words(words, count);
            return EXIT_FAILURE;
        }
        memcpy(words[i], initial[i], len);
    }

    print_words("Original list:", words, count);

    if (remove_words_containing(words, count, "ap", &new_count) != 0) {
        fprintf(stderr, "Failed to remove words\n");
        free_words(words, count);
        return EXIT_FAILURE;
    }

    print_words("After removal:", words, new_count);

    free_words(words, count);

    return EXIT_SUCCESS;
}