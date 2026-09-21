#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

static char *dup_string(const char *s)
{
    char *copy;
    size_t len;

    if (s == NULL) {
        return NULL;
    }

    len = strnlen(s, MAX_STRING_LEN);

    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, len);
    copy[len] = '\0';

    return copy;
}

size_t remove_words_containing(char **words, size_t count, const char *substr)
{
    size_t i;
    size_t write_idx;

    if (words == NULL || substr == NULL) {
        return count;
    }

    write_idx = 0;
    for (i = 0; i < count; i++) {
        if (words[i] != NULL && strstr(words[i], substr) != NULL) {
            free(words[i]);
            words[i] = NULL;
        } else {
            if (write_idx != i) {
                words[write_idx] = words[i];
                words[i] = NULL;
            }
            write_idx++;
        }
    }

    return write_idx;
}

static void print_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (words[i] != NULL) {
            printf("%s\n", words[i]);
        }
    }
}

static void free_words(char **words, size_t count)
{
    size_t i;

    if (words == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(words[i]);
        words[i] = NULL;
    }

    free(words);
}

int main(void)
{
    const char *initial[] = {
        "apple", "banana", "cherry", "grape", "apricot", "plum", "mango"
    };
    const char *target = "ap";
    char **words;
    size_t count;
    size_t new_count;
    size_t i;

    count = sizeof(initial) / sizeof(initial[0]);

    words = calloc(count, sizeof(*words));
    if (words == NULL) {
        fprintf(stderr, "Error: failed to allocate word list\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        words[i] = dup_string(initial[i]);
        if (words[i] == NULL) {
            fprintf(stderr, "Error: failed to allocate word\n");
            free_words(words, count);
            return EXIT_FAILURE;
        }
    }

    printf("Original list (%zu words):\n", count);
    print_words(words, count);

    new_count = remove_words_containing(words, count, target);

    printf("\nList after removing words containing \"%s\" (%zu words):\n",
           target, new_count);
    print_words(words, new_count);

    free_words(words, count);

    return EXIT_SUCCESS;
}