#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *my_strdup(const char *s) {
    size_t len;
    char *copy;
    if (s == NULL) {
        return NULL;
    }
    len = strnlen(s, (size_t)-1);
    copy = malloc(len + 1);
    if (copy != NULL) {
        snprintf(copy, len + 1, "%s", s);
    }
    return copy;
}

int remove_words_containing(char ***words, size_t *count, const char *target) {
    char **list;
    size_t n;
    size_t w = 0;
    size_t i;

    if (words == NULL || count == NULL || target == NULL) {
        return -1;
    }
    if (*words == NULL && *count != 0) {
        return -1;
    }
    if (*count == 0) {
        free(*words);
        *words = NULL;
        return 0;
    }

    list = *words;
    n = *count;

    for (i = 0; i < n; ++i) {
        if (list[i] != NULL && strstr(list[i], target) == NULL) {
            list[w++] = list[i];
        } else {
            free(list[i]);
        }
    }

    for (i = w; i < n; ++i) {
        list[i] = NULL;
    }

    *count = w;

    if (w == 0) {
        free(list);
        *words = NULL;
    } else {
        char **resized = realloc(list, w * sizeof(char *));
        if (resized != NULL) {
            *words = resized;
        }
    }

    return 0;
}

int main(void) {
    const char *initial[] = { "apple", "banana", "apricot", "cherry", "grape" };
    size_t count = sizeof(initial) / sizeof(initial[0]);
    char **words = malloc(count * sizeof(char *));
    size_t i;

    if (words == NULL) {
        return 1;
    }

    for (i = 0; i < count; ++i) {
        words[i] = my_strdup(initial[i]);
        if (words[i] == NULL) {
            size_t j;
            for (j = 0; j < i; ++j) {
                free(words[j]);
            }
            free(words);
            return 1;
        }
    }

    if (remove_words_containing(&words, &count, "ap") != 0) {
        for (i = 0; i < count; ++i) {
            free(words[i]);
        }
        free(words);
        return 1;
    }

    for (i = 0; i < count; ++i) {
        printf("%s\n", words[i]);
    }

    for (i = 0; i < count; ++i) {
        free(words[i]);
    }
    free(words);

    return 0;
}