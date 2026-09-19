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
    size_t alloc_count;
    int pattern_is_empty;

    if (out_count == NULL) {
        return NULL;
    }

    *out_count = 0;

    if (words == NULL || pattern == NULL) {
        return NULL;
    }

    alloc_count = (count == 0U) ? 1U : count;
    result = malloc(alloc_count * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    pattern_is_empty = (pattern[0] == '\0');

    kept = 0;
    for (i = 0; i < count; i++) {
        if (words[i] == NULL) {
            continue;
        }
        if (pattern_is_empty || strstr(words[i], pattern) == NULL) {
            result[kept] = duplicate_string(words[i]);
            if (result[kept] == NULL) {
                free_word_list(result, kept);
                return NULL;
            }
            kept++;
        }
    }

    if (kept > 0U && kept < count) {
        char **shrunk = realloc(result, kept * sizeof(*shrunk));
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    *out_count = kept;
    return result;
}

static int print_word_list(char **list, size_t count)
{
    size_t i;

    if (list == NULL && count > 0U) {
        return -1;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (printf("'%s'", list[i]) < 0) {
            return -1;
        }
        if (i + 1U < count) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *const words[] = {
        "Red", "", "Green", "Black", "Orange", "White", "Black"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *pattern = "Black";
    char **filtered;
    size_t filtered_count;

    filtered = remove_words(words, count, pattern, &filtered_count);
    if (filtered == NULL && filtered_count > 0U) {
        fprintf(stderr, "An error occurred.\n");
        return EXIT_FAILURE;
    }

    if (filtered == NULL) {
        if (printf("[]\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (print_word_list(filtered, filtered_count) < 0) {
        free_word_list(filtered, filtered_count);
        return EXIT_FAILURE;
    }

    free_word_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}