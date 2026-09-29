#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

static char *trim_copy(const char *src)
{
    size_t len;
    size_t start;
    size_t end;
    char *out;

    if (src == NULL) {
        return NULL;
    }

    len = strlen(src);
    start = 0;
    while (start < len && isspace((unsigned char)src[start])) {
        start++;
    }
    end = len;
    while (end > start && isspace((unsigned char)src[end - 1U])) {
        end--;
    }

    out = malloc((end - start) + 1U);
    if (out == NULL) {
        return NULL;
    }
    memcpy(out, src + start, end - start);
    out[end - start] = '\0';
    return out;
}

static char *remove_pattern(const char *src, const char *pattern)
{
    size_t src_len;
    size_t pat_len;
    size_t out_len;
    const char *cursor;
    const char *hit;
    char *copy;
    char *trimmed;
    char *dest;
    size_t tail;

    if (src == NULL || pattern == NULL) {
        return NULL;
    }

    src_len = strlen(src);
    pat_len = strlen(pattern);

    if (pat_len == 0U) {
        copy = malloc(src_len + 1U);
        if (copy == NULL) {
            return NULL;
        }
        memcpy(copy, src, src_len + 1U);
        trimmed = trim_copy(copy);
        free(copy);
        return trimmed;
    }

    out_len = 0U;
    cursor = src;
    while ((hit = strstr(cursor, pattern)) != NULL) {
        out_len += (size_t)(hit - cursor);
        cursor = hit + pat_len;
    }
    out_len += strlen(cursor);

    copy = malloc(out_len + 1U);
    if (copy == NULL) {
        return NULL;
    }

    dest = copy;
    cursor = src;
    while ((hit = strstr(cursor, pattern)) != NULL) {
        size_t chunk = (size_t)(hit - cursor);
        memcpy(dest, cursor, chunk);
        dest += chunk;
        cursor = hit + pat_len;
    }

    tail = strlen(cursor);
    memcpy(dest, cursor, tail);
    dest += tail;
    *dest = '\0';

    trimmed = trim_copy(copy);
    free(copy);
    return trimmed;
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