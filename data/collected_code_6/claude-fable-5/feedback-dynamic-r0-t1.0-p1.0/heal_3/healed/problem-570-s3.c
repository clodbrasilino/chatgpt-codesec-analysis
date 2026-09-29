#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src) + 1U;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);
    return copy;
}

static void free_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

static char **remove_words(const char *const *words, size_t count,
                           const char *pattern, size_t *out_count)
{
    char **result;
    size_t kept;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || pattern == NULL || count == 0U) {
        return NULL;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    kept = 0;
    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (strcmp(words[i], pattern) != 0) {
            result[kept] = duplicate_string(words[i]);
            if (result[kept] == NULL) {
                free_word_list(result, kept);
                return NULL;
            }
            kept++;
        }
    }

    if (kept == 0U) {
        free(result);
        return NULL;
    }

    if (kept < count) {
        char **shrunk = realloc(result, kept * sizeof(*shrunk));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *out_count = kept;
    return result;
}

int main(void)
{
    const char *const words[] = {
        "Red", "", "Green", "Black", "Orange", "White", "Black"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *pattern = "Black";
    char **filtered;
    size_t filtered_count = 0;
    size_t i;

    filtered = remove_words(words, count, pattern, &filtered_count);
    if (filtered == NULL) {
        fprintf(stderr, "No words remain or an error occurred.\n");
        return EXIT_FAILURE;
    }

    printf("[");
    for (i = 0; i < filtered_count; i++) {
        if (printf("'%s'%s", filtered[i],
                   (i + 1 < filtered_count) ? ", " : "") < 0) {
            free_word_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }
    printf("]\n");

    if (fflush(stdout) == EOF) {
        free_word_list(filtered, filtered_count);
        return EXIT_FAILURE;
    }

    free_word_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}