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
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  */

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
        if (strstr(words[i], pattern) == NULL) {
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
        "apple", "banana", "cherry", "grape", "apricot", "melon"
    };
    size_t count = sizeof(words) / sizeof(words[0]);
    const char *pattern = "ap";
    char **filtered;
    size_t filtered_count;
    size_t i;

    filtered = remove_words(words, count, pattern, &filtered_count);
    if (filtered == NULL) {
        if (fprintf(stderr, "No words remain or an error occurred.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < filtered_count; i++) {
        if (printf("%s\n", filtered[i]) < 0) {
            free_word_list(filtered, filtered_count);
            return EXIT_FAILURE;
        }
    }

    free_word_list(filtered, filtered_count);
    return EXIT_SUCCESS;
}