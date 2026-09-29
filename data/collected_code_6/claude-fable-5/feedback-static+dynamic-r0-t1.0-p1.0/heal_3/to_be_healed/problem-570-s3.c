#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *remove_pattern(const char *src, const char *pattern)
{
    size_t src_len;
    size_t pat_len;
    size_t out_len;
    const char *cursor;
    const char *hit;
    char *copy;
    char *dest;

    if (src == NULL || pattern == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    src_len = strlen(src);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pat_len = strlen(pattern);

    if (pat_len == 0U) {
        copy = malloc(src_len + 1U);
        if (copy == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, src, src_len + 1U);
        return copy;
    }

    out_len = 0U;
    cursor = src;
    while ((hit = strstr(cursor, pattern)) != NULL) {
        out_len += (size_t)(hit - cursor);
        cursor = hit + pat_len;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    out_len += strlen(cursor);

    copy = malloc(out_len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    dest = copy;
    cursor = src;
    while ((hit = strstr(cursor, pattern)) != NULL) {
        size_t chunk = (size_t)(hit - cursor);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, cursor, chunk);
        dest += chunk;
        cursor = hit + pat_len;
    }
    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t tail = strlen(cursor);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, cursor, tail);
        dest += tail;
    }
    *dest = '\0';

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
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
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

    if (count > SIZE_MAX / sizeof(*result)) {
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
        result[kept] = remove_pattern(words[i], pattern);
        if (result[kept] == NULL) {
            free_word_list(result, kept);
            return NULL;
        }
        kept++;
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