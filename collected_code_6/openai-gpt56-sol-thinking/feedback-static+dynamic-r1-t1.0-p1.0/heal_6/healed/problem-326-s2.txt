#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word_entry {
    const char *word;
    size_t count;
};

static char *duplicate_string(const char *source)
{
    const size_t length = strlen(source);
    char *copy;

    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

char *get_most_frequent_word(const char *const strings[], size_t count)
{
    struct word_entry *entries;
    size_t used = 0U;
    size_t best;
    size_t i;
    size_t j;
    char *result;

    if (strings == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (count == 0U) {
        errno = ENOENT;
        return NULL;
    }

    if (count > SIZE_MAX / sizeof(*entries)) {
        errno = EOVERFLOW;
        return NULL;
    }

    entries = malloc(count * sizeof(*entries));
    if (entries == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            free(entries);
            errno = EINVAL;
            return NULL;
        }

        if (strings[i][0] == '\0') {
            continue;
        }

        for (j = 0U; j < used; ++j) {
            if (strcmp(entries[j].word, strings[i]) == 0) {
                if (entries[j].count == SIZE_MAX) {
                    free(entries);
                    errno = EOVERFLOW;
                    return NULL;
                }

                ++entries[j].count;
                break;
            }
        }

        if (j == used) {
            entries[used].word = strings[i];
            entries[used].count = 1U;
            ++used;
        }
    }

    if (used == 0U) {
        free(entries);
        errno = ENOENT;
        return NULL;
    }

    best = 0U;

    for (i = 1U; i < used; ++i) {
        if (entries[i].count > entries[best].count) {
            best = i;
        }
    }

    result = duplicate_string(entries[best].word);
    if (result == NULL) {
        const int saved_errno = errno;

        free(entries);
        errno = saved_errno;
        return NULL;
    }

    free(entries);
    return result;
}

int main(int argc, char *const argv[])
{
    const char **strings;
    const char *program_name = "program";
    size_t count;
    size_t i;
    char *word;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc < 2 || argv == NULL) {
        fprintf(stderr, "Usage: %s <word> [word ...]\n", program_name);
        return EXIT_FAILURE;
    }

    count = (size_t)argc - 1U;

    if (count > SIZE_MAX / sizeof(*strings)) {
        fprintf(stderr, "Too many words\n");
        return EXIT_FAILURE;
    }

    strings = malloc(count * sizeof(*strings));
    if (strings == NULL) {
        errno = ENOMEM;
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        strings[i] = argv[i + 1U];
    }

    word = get_most_frequent_word(strings, count);
    if (word == NULL) {
        const int saved_errno = errno;

        free(strings);

        if (saved_errno == ENOENT) {
            fprintf(stderr, "No non-empty words were provided\n");
        } else {
            errno = saved_errno;
            perror("get_most_frequent_word");
        }

        return EXIT_FAILURE;
    }

    if (printf("%s\n", word) < 0) {
        const int saved_errno = errno;

        free(word);
        free(strings);
        errno = saved_errno;
        perror("printf");
        return EXIT_FAILURE;
    }

    free(word);
    free(strings);

    return EXIT_SUCCESS;
}